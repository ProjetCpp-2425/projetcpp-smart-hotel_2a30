#ifndef SERVICE_H
#define SERVICE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap>
#include <QDate>

class Service
{
    int id;
    QString type;
    double price;
    QString room;
    QDate dateCreation;

public:
    Service();
    Service(int, QString, double, QString, QDate);

    int getID() const;
    QString getType() const;
    double getPrice() const;
    QString getRoom() const;
    QDate getDateCreation() const;

    void setID(int id);
    void setType(const QString &t);
    void setPrice(double p);
    void setRoom(const QString &r);
    void setDateCreation(const QDate &date);

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    QSqlQueryModel *afficherParPrix(bool ascending);
    QSqlQueryModel *rechercherParID(const QString &id);
    QMap<QString, double> getStatistics();
    QString convertPrice(double priceInDTN, double exchangeRate);
};

#endif // SERVICE_H
