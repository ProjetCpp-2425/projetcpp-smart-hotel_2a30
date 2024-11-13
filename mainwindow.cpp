#include "employee.h"
#include "mainwindow.h"
#include "editemployee.h"
#include "ui_mainwindow.h"
#include "searchemployee.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QSqlError>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlTableModel>
#include <QRadioButton>
#include <QFileDialog>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QProcess>

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up validators for CIN and Phone fields (8 digits)
    QRegularExpression cinRegEx("\\d{8}");
    QValidator *cinValidator = new QRegularExpressionValidator(cinRegEx, this);
    ui->cinedit->setValidator(cinValidator);
    ui->numberedit->setValidator(cinValidator);

    // Set up email validator
    QRegularExpression emailRegEx("[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}");
    QValidator *emailValidator = new QRegularExpressionValidator(emailRegEx, this);
    ui->emailedit->setValidator(emailValidator);

    // Load employees into the table view on startup
    loadEmployeeData();

    // Connect Valid and Cancel buttons to their respective slots
    connect(ui->searchbutton, &QPushButton::clicked, this, &MainWindow::openSearchEmployeeWindow);
    connect(ui->idbutton, &QPushButton::clicked, this, &MainWindow::onSortByIdClicked);
    connect(ui->alphabutton, &QPushButton::clicked, this, &MainWindow::onSortByFullNameClicked);
    connect(ui->positionbutton, &QPushButton::clicked, this, &MainWindow::onSortByPositionClicked);

    connect(ui->validbutton, &QPushButton::clicked, this, &MainWindow::on_validbutton_clicked);
    connect(ui->removebutton, &QPushButton::clicked, this, &MainWindow::on_removebutton_clicked);
    connect(ui->editbutton, &QPushButton::clicked, this, &MainWindow::on_editbutton_clicked);
    connect(ui->generatePdfButton, &QPushButton::clicked, this, &MainWindow::generatePdf);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openSearchEmployeeWindow()
{
    // Create an instance of the search employee dialog
    searchemployee searchWindow(this); // assuming 'this' is the parent widget (main window)

    // Show the search employee dialog
    searchWindow.exec(); // This opens the dialog modally
}

// Function to load employee data from the database
void MainWindow::loadEmployeeData()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT CIN, IDSTAFF, FULLNAME, POSITION, SALARY, EMAIL, PHONE FROM EMPLOYEE");

    if (model->lastError().isValid()) {
        qDebug() << "Error loading data from database: " << model->lastError().text();
        return;
    }

    ui->employeeTableView->setModel(model);
    ui->employeeTableView->resizeColumnsToContents();
}

// Function to check uniqueness of a field in the EMPLOYEE table
bool MainWindow::isUnique(const QString &field, const QString &value, bool caseInsensitive) {
    QSqlQuery query;

    // Use case-insensitive comparison for IDSTAFF and EMAIL
    if (caseInsensitive) {
        query.prepare(QString("SELECT COUNT(*) FROM EMPLOYEE WHERE LOWER(%1) = LOWER(:value)").arg(field));
    } else {
        query.prepare(QString("SELECT COUNT(*) FROM EMPLOYEE WHERE %1 = :value").arg(field));
    }

    query.bindValue(":value", value);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() == 0;  // Returns true if no records match
    }
    return false;
}

// Slot to handle adding an employee when Valid button is clicked
void MainWindow::on_validbutton_clicked()
{
    // Retrieve data from the input fields
    QString fullname = ui->fullnameedit->text();
    QString email = ui->emailedit->text();
    QString position = ui->Postedit->text();
    QString phone = ui->numberedit->text();
    QString cin = ui->cinedit->text();
    QString id = ui->idedit->text();
    double salary = ui->salaryedit->text().toDouble();

    // Validation checks
    if (cin.length() != 8 || !cin.toUInt()) {
        QMessageBox::warning(this, "Validation Error", "CIN must be an 8-digit number.");
        return;
    }
    if (phone.length() != 8 || !phone.toUInt()) {
        QMessageBox::warning(this, "Validation Error", "Phone must be an 8-digit number.");
        return;
    }
    if (fullname.isEmpty() || id.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Name and ID cannot be empty.");
        return;
    }
    if (!ui->emailedit->hasAcceptableInput()) {
        QMessageBox::warning(this, "Validation Error", "Email format is invalid.");
        return;
    }
    if (salary <= 0) {
        QMessageBox::warning(this, "Validation Error", "Salary must be a positive number.");
        return;
    }

    // Uniqueness checks
    if (!isUnique("CIN", cin, false)) {
        QMessageBox::warning(this, "Validation Error", "CIN must be unique.");
        return;
    }
    if (!isUnique("IDSTAFF", id, true)) {
        QMessageBox::warning(this, "Validation Error", "ID Employee must be unique (case-insensitive).");
        return;
    }
    if (!isUnique("PHONE", phone, false)) {
        QMessageBox::warning(this, "Validation Error", "Phone number must be unique.");
        return;
    }
    if (!isUnique("EMAIL", email, true)) {
        QMessageBox::warning(this, "Validation Error", "Email must be unique (case-insensitive).");
        return;
    }

    // Insert new employee into the database
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEE (CIN, IDSTAFF, FULLNAME, POSITION, SALARY, EMAIL, PHONE) "
                  "VALUES (:cin, :idstaff, :fullname, :position, :salary, :email, :phone)");
    query.bindValue(":cin", cin);
    query.bindValue(":idstaff", id);
    query.bindValue(":fullname", fullname);
    query.bindValue(":position", position);
    query.bindValue(":salary", salary);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Employee added successfully.");
        loadEmployeeData();  // Reload the data to show the new entry

        // Run the Python script to send the email
        QProcess process;
        QStringList arguments;

        // Use the correct path to Python executable
        QString pythonPath = "C:\\Users\\medta\\AppData\\Local\\Programs\\Python\\Python313\\python.exe";
        arguments << "C:\\Users\\medta\\Desktop\\taha\\sendmail.py"
                  << email
                  << fullname
                  << position
                  << cin;

        // Start the process
        process.start(pythonPath, arguments);

        if (!process.waitForStarted()) {
            QMessageBox::warning(this, "Error", "Failed to start Python process: " + process.errorString());
            return;
        }

        if (!process.waitForFinished()) {
            QMessageBox::warning(this, "Error", "Python script did not finish: " + process.errorString());
            return;
        }

        // Capture the output and error messages
        QString output = process.readAllStandardOutput();
        QString errorOutput = process.readAllStandardError();

        if (!output.isEmpty()) {
            qDebug() << "Python script output: " << output;
        }

        if (!errorOutput.isEmpty()) {
            qDebug() << "Python script error: " << errorOutput;
            QMessageBox::warning(this, "Error", "Python script encountered an error: " + errorOutput);
        } else {
            QMessageBox::information(this, "Email Sent", "The notification email has been sent successfully.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to add employee: " + query.lastError().text());
    }
}


// Slot to handle removing an employee when Cancel button is clicked
void MainWindow::on_removebutton_clicked()
{
    QModelIndexList selectedRows = ui->employeeTableView->selectionModel()->selectedRows();

    if (!selectedRows.isEmpty()) {
        int row = selectedRows[0].row();
        QString cinemp = ui->employeeTableView->model()->index(row, 0).data().toString();  // Get CIN of selected employee

        QSqlQuery query;
        query.prepare("DELETE FROM EMPLOYEE WHERE CIN = :cin");
        query.bindValue(":cin", cinemp);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Employee removed successfully.");
            loadEmployeeData();  // Reload data after removal
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove employee: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Error", "No employee selected for removal.");
    }
}
void MainWindow::on_editbutton_clicked()
{
    QModelIndexList selectedRows = ui->employeeTableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        return; // No row selected
    }

    int rowIndex = selectedRows.first().row();

    // Get data from the selected row
    QString cin = ui->employeeTableView->model()->data(ui->employeeTableView->model()->index(rowIndex, 0)).toString();  // CIN
    QString idstaff = ui->employeeTableView->model()->data(ui->employeeTableView->model()->index(rowIndex, 1)).toString();  // ID
    QString fullname = ui->employeeTableView->model()->data(ui->employeeTableView->model()->index(rowIndex, 2)).toString();  // Full Name
    QString position = ui->employeeTableView->model()->data(ui->employeeTableView->model()->index(rowIndex, 3)).toString();  // Position
    double salary = ui->employeeTableView->model()->data(ui->employeeTableView->model()->index(rowIndex, 4)).toDouble();  // Salary
    QString email = ui->employeeTableView->model()->data(ui->employeeTableView->model()->index(rowIndex, 5)).toString();  // Email
    QString phone = ui->employeeTableView->model()->data(ui->employeeTableView->model()->index(rowIndex, 6)).toString();  // Phone

    // Create and set data in EditEmployee dialog
    EditEmployee *editDialog = new EditEmployee(this);
    editDialog->setEmployeeData(cin, idstaff, fullname, position, salary, email, phone);

    // Show the dialog
    editDialog->exec();
}


void MainWindow::onSortByIdClicked()
{
    // Sort by ID
    QString orderByClause = "IDSTAFF ASC";  // Sort in ascending order (or "DESC" for descending)
    sortEmployeeTable(orderByClause);
}

void MainWindow::onSortByFullNameClicked()
{
    // Sort alphabetically by full name
    QString orderByClause = "FULLNAME ASC";  // Alphabetical order
    sortEmployeeTable(orderByClause);
}

void MainWindow::onSortByPositionClicked()
{
    // Sort by position
    QString orderByClause = "POSITION ASC";  // Alphabetical order by position
    sortEmployeeTable(orderByClause);
}
void MainWindow::sortEmployeeTable(const QString &orderByClause)
{
    // Create a new query with ORDER BY to sort
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString query = QString("SELECT CIN, IDSTAFF, FULLNAME, POSITION, SALARY, EMAIL, PHONE FROM EMPLOYEE ORDER BY %1").arg(orderByClause);
    model->setQuery(query);

    // Check for query errors
    if (model->lastError().isValid()) {
        qDebug() << "Error sorting data: " << model->lastError().text();
        return;
    }

    // Set the sorted model to the table view
    ui->employeeTableView->setModel(model);
}
void MainWindow::generatePdf()
{
    // Open a file dialog to select the save location and filename
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));

    if (fileName.isEmpty()) return;

    // Create a PDF writer object
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define colors
    QColor richBlack("#021024");
    QColor oxfordBlue("#0C1D49");
    QColor indigoDye("#26425A");

    // Draw title in a large, bold font with Oxford Blue color
    QFont titleFont("Arial", 18, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(oxfordBlue);
    painter.drawText(100, 100, "PDF File - Employee Data");

    // Draw date of exportation at the bottom of the PDF
    QFont footerFont("Arial", 10);
    painter.setFont(footerFont);
    painter.setPen(richBlack);
    painter.drawText(100, pdfWriter.height() - 50, "Exported on: " + QDate::currentDate().toString("dd-MM-yyyy"));

    // Load and draw the logo at the bottom right corner
    QImage logo(":/logo.png");  // Use resource path if added as resource
    if (!logo.isNull()) {
        int logoX = pdfWriter.width() - logo.width() - 50;
        int logoY = pdfWriter.height() - logo.height() - 50;
        painter.drawImage(logoX, logoY, logo);
    } else {
        qDebug() << "Failed to load logo.png";
    }

    // Text settings for employee data
    QFont font("Arial", 12);
    painter.setFont(font);

    int yOffset = 200;
    int i = 1;

    QSqlQuery query("SELECT cin, idstaff, fullname, position, salary, email, phone FROM employee");
    while (query.next()) {
        painter.setPen(indigoDye);
        painter.drawText(50, yOffset, "Employee " + QString::number(i) + ":");
        i++;
        yOffset += 70;

        // Print each employee's data in the specified format and color
        painter.setPen(richBlack);
        painter.drawText(100, yOffset, "CIN: " + query.value("cin").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "ID Staff: " + query.value("idstaff").toString());
        yOffset += 70;
        painter.setPen(oxfordBlue);
        painter.drawText(100, yOffset, "Full Name: " + query.value("fullname").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Position: " + query.value("position").toString());
        yOffset += 70;
        painter.setPen(indigoDye);
        painter.drawText(100, yOffset, "Salary: " + query.value("salary").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Email: " + query.value("email").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Phone: " + query.value("phone").toString());

        yOffset += 70;  // Add space between employees
    }

    painter.end();
    QMessageBox::information(this, tr("PDF Generated"), tr("The employee data has been saved as a PDF."));
}
