#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QAudioSource>
#include <QMediaDevices>
#include <QAudioFormat>
#include <QBuffer>
#include <QTimer>
#include <QProgressBar>

class AudioRecorder : public QObject {
    Q_OBJECT

public:
    explicit AudioRecorder(QObject *parent = nullptr);
    ~AudioRecorder();

    void startRecording(int durationMs = 40000);
    void stopRecording();
    bool isRecording() const { return m_isRecording; }

signals:
    void recordingStarted();
    void recordingStopped();
    void recordingProgress(int seconds);
    void recordingComplete(const QByteArray &audioData);
    void error(const QString &message);

private slots:
    void handleRecordingTimeout();

private:
    QByteArray createWavHeader() const;
    void updateWavHeader(QByteArray &audioData);

    QAudioSource *m_audioSource;
    QBuffer *m_audioBuffer;
    QTimer *m_progressTimer;
    bool m_isRecording;
    int m_duration;
};

#endif // AUDIORECORDER_H
