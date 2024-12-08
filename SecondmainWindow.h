#ifndef SECONDMAINWINDOW_H
#define SECONDMAINWINDOW_H
#include <QString>

#include "service.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SecondmainWindow; }
QT_END_NAMESPACE

class SecondmainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondmainWindow(QWidget *parent = nullptr);
    ~SecondmainWindow();

private slots:
    void on_pb1_clicked();
    void on_pb2_clicked();
    void on_pb3_clicked();
    void on_pushButton_T_clicked();
    void on_searchButton_clicked();
    void on_pushButton_Stats_clicked();
    void on_pushButton_Export_clicked();
    void on_pushButton_Convert_clicked(); // Added for price conversion

    void on_start_listening_5_clicked();

    void on_button5_clicked();

private:
    Ui::SecondmainWindow *ui;
    Service Etmp;
    bool sortAscending = true;
signals:
    void closeEventTriggered();
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
