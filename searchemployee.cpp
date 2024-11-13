#include "searchemployee.h"
#include "ui_searchemployee.h"
#include <QMessageBox>
#include <QSqlQueryModel>

searchemployee::searchemployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchemployee)
{
    ui->setupUi(this);

    // Initializing the table view
    ui->searchTableView->setModel(new QSqlQueryModel());  // Empty model initially
}

searchemployee::~searchemployee()
{
    delete ui;
}

void searchemployee::on_confirmButton_clicked()
{
    QString searchText = ui->searchLineEdit->text();
    QString searchCriterion;

    // Check which radio button is selected to determine the search criterion
    if (ui->id1button->isChecked()) {
        searchCriterion = "idstaff";
    } else if (ui->fullnamebutton->isChecked()) {
        searchCriterion = "fullname";
    } else if (ui->position1button->isChecked()) {
        searchCriterion = "position";
    } else {
        QMessageBox::warning(this, "Search Error", "Please select a search criterion.");
        return;
    }

    // Query the database for employees matching the search criteria
    QSqlQueryModel* model = employee.displayEmployees();
    model->setQuery("SELECT * FROM employee WHERE " + searchCriterion + " LIKE '%" + searchText + "%'");

    // Check if the query was successful
    if (model->lastError().isValid()) {
        QMessageBox::warning(this, "Query Error", "An error occurred while searching: " + model->lastError().text());
        return;
    }

    // Set the model to the table view to display the results
    ui->searchTableView->setModel(model);
}

void searchemployee::on_cancel0button_clicked()
{
    // Close the dialog when cancel button is clicked
    close();
}
