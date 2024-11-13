#include "stat.h"
#include "ui_stat.h"
#include "employee.h"

stat::stat(QWidget *parent) :
    QDialog(parent), // Call QDialog constructor here
    ui(new Ui::stat)
{
    ui->setupUi(this);
    showStatistics();
}

stat::~stat()
{
    delete ui;
}

// This method will fetch and display the statistics
void stat::showStatistics() {
    Employee employee;
    QSqlQueryModel *model = employee.getPositionStatistics();

    // Assuming ui->tableView is your QTableView in the stat.ui
    ui->tableView->setModel(model);
}
