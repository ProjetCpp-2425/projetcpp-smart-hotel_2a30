#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt Core
#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QList>
#include "SecondmainWindow.h"
// Qt SQL
#include <QSqlDatabase>

// Qt Network
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

// Qt Multimedia
#include <QAudioDevice>
#include <QMediaDevices>

// Qt Widgets
#include <QTableWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

// Custom Classes
#include "transaction.h"
#include "expense.h"
#include "statistics.h"
#include "audiorecorder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase db;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void connectToDatabase();
   QVector<Transaction> getTransactions();
   QVector<Expense> getExpenses();
//void showEvent(QShowEvent* event) override;
//void showLossNotification();
    QList<Transaction> *executeQuery(QString request);
    QString escapeCsvValue(const QString &value);
    QString exportTableToexcel(QTableWidget* table);
    QList<int>* getTransactionYears(QVector<Transaction> transactions);
    Statistics fillStatestics(QVector<Transaction> transactions,int year);
    void updateChart();
    void onComboBoxIdValueChanged(int row,int index,const int &id);
    void showToastNotification(const QString &title,const QString &message);
    void showNotification(QSystemTrayIcon* tryIcon,const QString &title,const QString &message);
    void showNotification(const QString& title, const QString& message, const QString& iconPath);
    void checkMonthlyLoss(double totalIncome, double totalExpenses) ;
    void addExpense(int);
    QVector<QString> getTransactionIds();
private slots:
    void on_typeRecord_currentIndexChanged(int index);
  //  void checkForLoss();



    void on_pushButton_17_clicked();

    void on_listTransaction_cellDoubleClicked(int row, int column);

    void on_typeRecord_2_currentIndexChanged(int index);

    void on_typeRecord_2_currentTextChanged(const QString &arg1);
    void onSpeechReconnitionFinished(QNetworkReply*);


    void on_pushButton_15_clicked();

    void on_pushButton_2_clicked();

    void on_widget_16_customContextMenuRequested(const QPoint &pos);

   // void on_lineEdit_textChanged(const QString &arg1);

    void on_date_Search_textChanged(const QString &arg1);

    void on_search_id_textChanged(const QString &arg1);

    void on_cmbTransactionYears_currentTextChanged(const QString &arg1);

    void on_cmbTransactionYears_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_start_listening_clicked();

    void on_end_listening_clicked();

    void on_pushButton_4_clicked();

    void on_start_listening_5_clicked();

    void on_button5_clicked();

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    SecondmainWindow * secondwindow=nullptr;
    void startSpeechReconnition(const QByteArray &audioData);
    void processVoiceCommand(const QString &command);
    QNetworkAccessManager *networkManager;
    void pollTranscriptionResult(const QString &apiKey, const QString &id);
    AudioRecorder *audioRecorder;

};
#endif // MAINWINDOW_H
