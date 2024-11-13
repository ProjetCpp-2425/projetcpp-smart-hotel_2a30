#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "connection.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employee {
public:
    // Default constructor
    Employee();

    // Parameterized constructor
    Employee(int cin, QString idstaff, QString fullname, QString name, QString position, float salary, QString email, int phone);

    // Getters
    int getCin();
    QString getIdstaff();
    QString getfullname();
    QString getName();
    QString getPosition();
    double getSalary();
    QString getEmail();
    int getPhone();

    // Setters
    void setCin(int cin);
    void setIdstaff(QString idstaff);
    void setfullname(QString fullname);
    void setName(QString name);
    void setPosition(QString position);
    void setSalary(float salary);
    void setEmail(QString email);
    void setPhone(int phone);

    // Database operations
    bool addEmployee();
    QSqlQueryModel* displayEmployees();
    bool deleteEmployee(QString idstaff);
    bool editEmployee(QString idstaff);
    QSqlQueryModel* sortEmployees(QString criterion);

private:
    int cin;               // Employee CIN
    QString idstaff;       // Employee ID
    QString fullname;       // fullname
    QString name;          // Name
    QString position;      // Position
    double salary;         // Salary
    QString email;         // Email
    int phone;             // Phone number
};

#endif // EMPLOYEE_H
