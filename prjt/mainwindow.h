#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>

#include "service.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb1_clicked();
    void on_pb2_clicked();
    void on_pb3_clicked();
    void on_pushButton_T_clicked();
    void on_searchButton_clicked();
    void on_pushButton_Stats_clicked();
    void on_pushButton_Export_clicked();
    void on_pushButton_Convert_clicked(); // Added for price conversion

private:
    Ui::MainWindow *ui;
    Service Etmp;
    bool sortAscending = true;
};

#endif // MAINWINDOW_H
