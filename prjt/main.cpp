#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    bool test = c.createconnect();  // Create database connection
    MainWindow w;

    if (test)
    {
        w.show();  // Show the main window
        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("Connection to the database successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"),
                              QObject::tr("Connection to the database failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return -1;  // Exit if connection fails
    }

    return a.exec();  // Start the application event loop
}
