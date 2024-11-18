#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMainWindow>
#include "service.h" // Include the Service class
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    Connection();
    bool createconnect();
};


#endif // MAINWINDOW_H
