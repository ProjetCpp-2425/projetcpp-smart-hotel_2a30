#ifndef EDITEMPLOYEE_H
#define EDITEMPLOYEE_H

#include <QDialog>

namespace Ui {
class EditEmployee;
}

class EditEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit EditEmployee(QWidget *parent = nullptr);
    ~EditEmployee();

    // Set employee data in the dialog fields
    void setEmployeeData(const QString &cin, const QString &idstaff, const QString &fullname,
                         const QString &position, double salary, const QString &email, const QString &phone);

    // Update employee information in the database
    bool updateEmployeeInDatabase();

private:
    Ui::EditEmployee *ui;
    QString currentCin; // Store the CIN to identify the employee
};

#endif // EDITEMPLOYEE_H
