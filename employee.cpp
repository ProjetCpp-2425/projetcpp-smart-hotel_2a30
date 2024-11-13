#include "employee.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

// Default constructor
Employee::Employee() {}

// Parameterized constructor
Employee::Employee(int cin, QString idstaff, QString fullname, QString name, QString position, float salary, QString email, int phone) {
    this->cin = cin;
    this->idstaff = idstaff;
    this->fullname = fullname;
    this->name = name;
    this->position = position;
    this->salary = salary;
    this->email = email;
    this->phone = phone;
}

// Getters
int Employee::getCin() { return cin; }
QString Employee::getIdstaff() { return idstaff; }
QString Employee::getfullname() { return fullname; }
QString Employee::getName() { return name; }
QString Employee::getPosition() { return position; }
double Employee::getSalary() { return salary; }
QString Employee::getEmail() { return email; }
int Employee::getPhone() { return phone; }

// Setters
void Employee::setCin(int cin) { this->cin = cin; }
void Employee::setIdstaff(QString idstaff) { this->idstaff = idstaff; }
void Employee::setfullname(QString fullname) { this->fullname = fullname; }
void Employee::setName(QString name) { this->name = name; }
void Employee::setPosition(QString position) { this->position = position; }
void Employee::setSalary(float salary) { this->salary = salary; }
void Employee::setEmail(QString email) { this->email = email; }
void Employee::setPhone(int phone) { this->phone = phone; }

// Adding a new employee
bool Employee::addEmployee() {
    QSqlQuery query;
    query.prepare("INSERT INTO employee (cin, idstaff, fullname, position, salary, email, phone) "
                  "VALUES (:cin, :idstaff, :fullname, :position, :salary, :email, :phone)");
    query.bindValue(":cin", cin);
    query.bindValue(":idstaff", idstaff);
    query.bindValue(":fullname", fullname);
    query.bindValue(":position", position);
    query.bindValue(":salary", salary);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);

    if (!query.exec()) {
        qDebug() << "Add employee error:" << query.lastError().text();
        return false;
    }
    return true;
}


// Displaying all employees
QSqlQueryModel* Employee::displayEmployees() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employee");
    return model;
}

// Deleting an employee by ID
bool Employee::deleteEmployee(QString idstaff) {
    QSqlQuery query;
    query.prepare("DELETE FROM employee WHERE idstaff = :idstaff");
    query.bindValue(":idstaff", idstaff);

    return query.exec();
}

// Editing an employee by ID
bool Employee::editEmployee(QString idstaff) {
    QSqlQuery query;
    query.prepare("UPDATE employee SET fullname = :fullname, name = :name, position = :position, salary = :salary, email = :email, "
                  "phone = :phone WHERE idstaff = :idstaff");
    query.bindValue(":idstaff", idstaff);
    query.bindValue(":fullname", fullname);
    query.bindValue(":name", name);
    query.bindValue(":position", position);
    query.bindValue(":salary", salary);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);

    return query.exec();
}

// Sorting employees based on a criterion
QSqlQueryModel* Employee::sortEmployees(QString criterion) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM employee ORDER BY " + criterion;
    model->setQuery(queryStr);
    return model;
}
/*
QSqlQueryModel* Employee::getPositionStatistics() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT position, COUNT(*) as employee_count FROM employee GROUP BY position");
    return model;
}
*/
