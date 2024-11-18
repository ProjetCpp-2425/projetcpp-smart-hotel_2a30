#include "service.h"
#include <QSqlError>  // Include for error handling
#include <QString>

Service::Service() : id(0), type(""), price(0.0), room(""), dateCreation(QDate::currentDate()) {
    // Default constructor body
}

Service::Service(int id, QString type, double price, QString room, QDate dateCreation) {
    this->id = id;
    this->type = type;
    this->price = price;
    this->room = room;
    this->dateCreation = dateCreation;
}

bool Service::ajouter() {
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("INSERT INTO SERVICE (ID, TYPE, PRICE, ROOM, DATE_CREATION) "
                  "VALUES (:ID, :TYPE, :PRICE, :ROOM, :DATE_CREATION)");
    query.bindValue(":ID", res);
    query.bindValue(":TYPE", type);
    query.bindValue(":PRICE", price);
    query.bindValue(":ROOM", room);
    query.bindValue(":DATE_CREATION", dateCreation);

    return query.exec();
}

QSqlQueryModel * Service::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM SERVICE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Room"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Creation"));

    return model;
}

bool Service::supprimer(int id) {
    // First, check if the ID exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM SERVICE WHERE ID = :id");
    checkQuery.bindValue(":id", id);

    if (!checkQuery.exec() || !checkQuery.next() || checkQuery.value(0).toInt() == 0) {
        qDebug() << "Service with ID" << id << "does not exist.";
        return false; // ID does not exist
    }

    // Proceed to delete
    QSqlQuery query;
    query.prepare("DELETE FROM SERVICE WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Delete failed: " << query.lastError().text(); // Log the error
        return false; // Indicate failure
    }

    return true; // Indicate success
}

QSqlQueryModel* Service::afficherParPrix(bool ascending)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Construct the SQL query based on the sorting order
    QString queryStr = ascending
            ? "SELECT * FROM SERVICE ORDER BY PRICE ASC"
            : "SELECT * FROM SERVICE ORDER BY PRICE DESC";

    // Execute the query and set the model
    model->setQuery(queryStr);

    // Set header labels for better display
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Price"));

    return model;
}

QSqlQueryModel* Service::rechercherParID(const QString &id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the query to search for a service by its ID
    query.prepare("SELECT * FROM SERVICE WHERE ID LIKE :id");
    query.bindValue(":id", "%" + id + "%");  // Use wildcards for partial matches
    query.exec();

    // Set the query model
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Price"));

    return model;
}

QMap<QString, double> Service::getStatistics()
{
    QMap<QString, double> stats;
    QSqlQuery query;

    // Total price
    query.exec("SELECT SUM(PRICE) FROM SERVICE");
    if (query.next()) {
        stats["total"] = query.value(0).toDouble();
    }

    // Average price
    query.exec("SELECT AVG(PRICE) FROM SERVICE");
    if (query.next()) {
        stats["average"] = query.value(0).toDouble();
    }

    // Minimum price
    query.exec("SELECT MIN(PRICE) FROM SERVICE");
    if (query.next()) {
        stats["min"] = query.value(0).toDouble();
    }

    // Maximum price
    query.exec("SELECT MAX(PRICE) FROM SERVICE");
    if (query.next()) {
        stats["max"] = query.value(0).toDouble();
    }

    return stats;
}

Service::Service() : id(0), type(""), price(0.0), room(""), dateCreation(QDate::currentDate()) {}

Service::Service(int id, QString type, double price, QString room, QDate dateCreation) :
    id(id), type(type), price(price), room(room), dateCreation(dateCreation) {}

QString Service::convertPrice(double priceInDTN, double exchangeRate) {
    return QString::number(priceInDTN * exchangeRate, 'f', 2);
}
