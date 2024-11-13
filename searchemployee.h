#ifndef SEARCHEMPLOYEE_H
#define SEARCHEMPLOYEE_H

#include <QDialog>
#include <QSqlQueryModel>
#include "employee.h"  // Include the Employee class header

namespace Ui {
class searchemployee;
}

class searchemployee : public QDialog
{
    Q_OBJECT

public:
    explicit searchemployee(QWidget *parent = nullptr);
    ~searchemployee();

private slots:
    void on_confirmButton_clicked();  // Slot to handle search
    void on_cancel0button_clicked();  // Slot to handle cancel

private:
    Ui::searchemployee *ui;
    Employee employee;  // Instance of Employee class for database interaction
};

#endif // SEARCHEMPLOYEE_H
