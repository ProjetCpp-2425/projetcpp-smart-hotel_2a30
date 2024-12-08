#ifndef TRANSACTION_H
#define TRANSACTION_H
#include<string>
#include<QDate>
using namespace std;


class Transaction
{
public:
    Transaction();
    Transaction(int id, const QString &type, const QString &category, const QDate &date, const QString &paymentMethod, double amount);



    int getId() const;
    void setId(int newId);
    const QString &getType() const;
    void setType(const QString &newType);
    const QString &getCategory() const;
    void setCategory(const QString &newCategory);
    const QDate &getDate() const;
    void setDate(const QDate &newDate);
    const QString &getPaymentMethod() const;
    void setPaymentMethod(const QString &newPaymentMethod);
    double getAmount() const;
    void setAmount(double newAmount);

private:
    int id;
    QString type;
    QString category;
    QDate date;
    QString paymentMethod;
    double amount;


};

#endif // TRANSACTION_H
