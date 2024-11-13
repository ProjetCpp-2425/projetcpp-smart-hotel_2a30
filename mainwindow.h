#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSearchEmployeeWindow();
    void generatePdf();
    void onSortByIdClicked();
    void onSortByFullNameClicked();
    void onSortByPositionClicked();
    void sortEmployeeTable(const QString &orderByClause);
    void loadEmployeeData();                // Loads employee data into the table view
    void on_validbutton_clicked();          // Handles adding an employee
    void on_removebutton_clicked();         // Handles removing an employee
    bool isUnique(const QString &field, const QString &value, bool caseInsensitive);
    void on_editbutton_clicked();           // edit button functions


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
