/*#include "connection.h"
Connection::Connection(){}
bool Connection::createconnect()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("CPP_Project");
db.setUserName("Fares");
db.setPassword("0000");
if (db.open()) test=true;
    return  test;
}
void Connection::closeConnection(){db.close();}*/

#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("CPP_Project");//inserer le nom de la source de données
db.setUserName("Fares");//inserer nom de l'utilisateur
db.setPassword("0000");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
