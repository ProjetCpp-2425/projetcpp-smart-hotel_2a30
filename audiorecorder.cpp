#include "audiorecorder.h"
#include <QDataStream>

AudioRecorder::AudioRecorder(QObject *parent)
    : QObject(parent)
        , m_audioSource(nullptr)
        , m_audioBuffer(nullptr)
        , m_progressTimer(nullptr)
        , m_isRecording(false)
        , m_duration(0)
    {
}

AudioRecorder::~AudioRecorder()
{
    stopRecording();
}

void AudioRecorder::startRecording(int durationMs)
{
    if (m_isRecording) {
            emit error("Recording already in progress");
            return;
        }

        // Get the default audio input device
        QAudioDevice audioDevice = QMediaDevices::defaultAudioInput();
        if (audioDevice.isNull()) {
            emit error("No audio input device found");
            return;
        }

        // Configure audio format
        QAudioFormat format;
        format.setSampleRate(44100); // Standard sample rate
        format.setChannelCount(2);  // Stereo
        format.setSampleFormat(QAudioFormat::Int16); // 16-bit samples

        // Check if the format is supported
        if (!audioDevice.isFormatSupported(format)) {
            emit error("Requested audio format is not supported by the device");
            return;
        }

        // Create and set up the audio buffer
        m_audioBuffer = new QBuffer(this);
        if (!m_audioBuffer->open(QIODevice::WriteOnly)) {
            emit error("Failed to open audio buffer");
            delete m_audioBuffer;
            m_audioBuffer = nullptr;
            return;
        }

        // Write WAV header to the buffer
        m_audioBuffer->write(createWavHeader());

        // Create and start the audio source
        m_audioSource = new QAudioSource(audioDevice, format, this);
        m_audioSource->start(m_audioBuffer);

        // Set up a progress timer to emit recording progress
        m_progressTimer = new QTimer(this);
        connect(m_progressTimer, &QTimer::timeout, this, [this]() {
            emit recordingProgress(m_progressTimer->interval() *
                                   m_progressTimer->property("count").toInt() / 1000);
            m_progressTimer->setProperty("count",
                                         m_progressTimer->property("count").toInt() + 1);
        });
        m_progressTimer->setProperty("count", 0);
        m_progressTimer->start(100); // Update every 100ms

        m_isRecording = true;
        m_duration = durationMs;
        emit recordingStarted();

        // Stop recording after the specified duration
        QTimer::singleShot(durationMs, this, &AudioRecorder::handleRecordingTimeout);
}

void AudioRecorder::stopRecording()
{
    if (!m_isRecording) {
            return;
        }

        if (m_audioSource) {
            m_audioSource->stop();
            delete m_audioSource;
            m_audioSource = nullptr;
        }

        if (m_progressTimer) {
            m_progressTimer->stop();
            delete m_progressTimer;
            m_progressTimer = nullptr;
        }

        if (m_audioBuffer) {
            QByteArray audioData = m_audioBuffer->buffer();
            updateWavHeader(audioData);
            emit recordingComplete(audioData);

            m_audioBuffer->close();
            delete m_audioBuffer;
            m_audioBuffer = nullptr;
        }

        m_isRecording = false;
        emit recordingStopped();
}

void AudioRecorder::handleRecordingTimeout()
{
    if (m_isRecording) {
            stopRecording();
        }
}

QByteArray AudioRecorder::createWavHeader() const
{
    QByteArray headerData;
        QDataStream headerStream(&headerData, QIODevice::WriteOnly);
        headerStream.setByteOrder(QDataStream::LittleEndian);

        // RIFF header
        headerStream.writeRawData("RIFF", 4);
        headerStream.writeRawData("\0\0\0\0", 4);  // Placeholder for file size
        headerStream.writeRawData("WAVE", 4);

        // Format chunk
        headerStream.writeRawData("fmt ", 4);
        headerStream << quint32(16);                // Format chunk size
        headerStream << quint16(1);                 // Audio format (PCM)
        headerStream << quint16(2);                 // Channels (Stereo)
        headerStream << quint32(44100);             // Sample rate
        headerStream << quint32(44100 * 2 * 16 / 8); // Byte rate
        headerStream << quint16(2 * 16 / 8);         // Block align
        headerStream << quint16(16);                // Bits per sample

        // Data chunk
        headerStream.writeRawData("data", 4);
        headerStream.writeRawData("\0\0\0\0", 4);  // Placeholder for data size

        return headerData;
}

void AudioRecorder::updateWavHeader(QByteArray &audioData)
{
    qint32 fileSize = audioData.size() - 8;
        qint32 dataSize = audioData.size() - 44;

        // Update file size
        audioData.replace(4, 4, reinterpret_cast<char*>(&fileSize), 4);
        // Update data size
        audioData.replace(40, 4, reinterpret_cast<char*>(&dataSize), 4);
}
