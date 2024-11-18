#include "mainwindow.h"
#include <QString>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb1_clicked()
{
    int id = ui->lineEdit_ID->text().toInt();
    QString type = ui->lineEdit_Type->text();
    double price = ui->lineEdit_Price->text().toDouble();
    QString room = ui->lineEdit_Room->text();
    QDate dateCreation = QDate::currentDate();

    Service S(id, type, price, room, dateCreation);
    bool test = S.ajouter();

    if (test) {
        QMessageBox::information(this, "Success", "Service added successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to add the service.");
    }
}

void MainWindow::on_pb2_clicked()
{
    ui->tableView->setModel(Etmp.afficher());
}

void MainWindow::on_pb3_clicked()
{
    int id = ui->lineEdit_ID->text().toInt();
    bool test = Etmp.supprimer(id);

    if (test) {
        QMessageBox::information(this, "Success", "Service deleted successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete the service.");
    }
}

void MainWindow::on_pushButton_T_clicked()
{
    sortAscending = !sortAscending;
    ui->tableView->setModel(Etmp.afficherParPrix(sortAscending));
}

void MainWindow::on_searchButton_clicked()
{
    QString searchText = ui->lineEdit_search->text();
    ui->tableView->setModel(Etmp.rechercherParID(searchText));
}

void MainWindow::on_pushButton_Stats_clicked()
{
    if (ui->graphicsView->scene() != nullptr) {
        ui->graphicsView->scene()->clear();
    } else {
        ui->graphicsView->setScene(new QGraphicsScene(this));
    }

    QMap<QString, double> stats = Etmp.getStatistics();

    QBarSet *set = new QBarSet("Prix");
    *set << stats["total"] << stats["average"] << stats["min"] << stats["max"];

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Prix des Services");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Total" << "Moyenne" << "Minimum" << "Maximum";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, stats["total"] * 1.1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(521, 401);

    ui->graphicsView->scene()->addWidget(chartView);
}

void MainWindow::on_pushButton_Export_clicked()
{
    QString filePath = "services_list.pdf";
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPagedPaintDevice::A4);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Arial", 10));

    int xOffset = 30, yOffset = 150;
    int rowHeight = 40;
    int columnWidth = 150;

    painter.drawText(xOffset, yOffset - 50, "Liste des Services");
    painter.drawText(xOffset, yOffset, "ID");
    painter.drawText(xOffset + columnWidth, yOffset, "Type");
    painter.drawText(xOffset + 2 * columnWidth, yOffset, "Prix");

    yOffset += rowHeight;
    painter.drawLine(xOffset, yOffset, xOffset + 3 * columnWidth, yOffset);
    yOffset += rowHeight;

    QSqlQueryModel *model = Etmp.afficher();
    int rowCount = model->rowCount();

    for (int row = 0; row < rowCount; ++row) {
        painter.drawText(xOffset, yOffset, model->data(model->index(row, 0)).toString());
        painter.drawText(xOffset + columnWidth, yOffset, model->data(model->index(row, 1)).toString());
        painter.drawText(xOffset + 2 * columnWidth, yOffset, model->data(model->index(row, 2)).toString());
        yOffset += rowHeight;

        if (yOffset > pdfWriter.height() - 100) {
            pdfWriter.newPage();
            yOffset = 100;
        }
    }

    painter.end();
    QMessageBox::information(this, "Export Success", "PDF saved to: " + filePath);
}

void MainWindow::on_pushButton_Convert_clicked()
{
    double price = ui->lineEdit_Price->text().toDouble();
    double exchangeRate = ui->lineEdit_ExchangeRate->text().toDouble();
    QString convertedPrice = Etmp.convertPrice(price, exchangeRate);
    ui->label_ConvertedPrice->setText("Converted Price: " + convertedPrice);
}
