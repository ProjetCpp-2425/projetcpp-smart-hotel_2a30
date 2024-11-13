#include "editemployee.h"
#include "ui_editemployee.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

EditEmployee::EditEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployee)
{
    ui->setupUi(this);
    // Connect the "OK" button to the accept slot
    connect(ui->okbutton, &QPushButton::clicked, this, &EditEmployee::accept);

    // Connect the "Cancel" button to the reject slot
    connect(ui->cancelbutton, &QPushButton::clicked, this, &EditEmployee::reject);
}

EditEmployee::~EditEmployee()
{
    delete ui;
}

// Set the current employee data into the dialog's fields
void EditEmployee::setEmployeeData(const QString &cin, const QString &idstaff, const QString &fullname,
                                   const QString &position, double salary, const QString &email,
                                   const QString &phone)
{
    currentCin = cin;  // Store the CIN to identify the employee later during the update
    ui->cinLineEdit->setText(cin);
    ui->idstaffLineEdit->setText(idstaff);
    ui->fullnameLineEdit->setText(fullname);
    ui->positionLineEdit->setText(position);
    ui->salaryLineEdit->setText(QString::number(salary));
    ui->emailLineEdit->setText(email);
    ui->phoneLineEdit->setText(phone);
}

// Update the employee's information in the database
bool EditEmployee::updateEmployeeInDatabase()
{
    QSqlQuery query;
    query.prepare("UPDATE employee SET "
                  "idstaff = :idstaff, fullname = :fullname, position = :position, salary = :salary, "
                  "email = :email, phone = :phone "
                  "WHERE cin = :cin");

    query.bindValue(":idstaff", ui->idstaffLineEdit->text());
    query.bindValue(":fullname", ui->fullnameLineEdit->text());
    query.bindValue(":position", ui->positionLineEdit->text());
    query.bindValue(":salary", ui->salaryLineEdit->text().toDouble());
    query.bindValue(":email", ui->emailLineEdit->text());
    query.bindValue(":phone", ui->phoneLineEdit->text());
    query.bindValue(":cin", currentCin);  // Use the stored CIN to update the correct employee

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Employee updated successfully.");
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to update employee: " + query.lastError().text());
        return false;
    }
}
