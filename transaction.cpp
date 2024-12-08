#include "transaction.h"

Transaction::Transaction()
{

}

int Transaction::getId() const
{
    return id;
}

void Transaction::setId(int newId)
{
    id = newId;
}

const QString &Transaction::getType() const
{
    return type;
}

void Transaction::setType(const QString &newType)
{
    type = newType;
}

const QString &Transaction::getCategory() const
{
    return category;
}

void Transaction::setCategory(const QString &newCategory)
{
    category = newCategory;
}

const QDate &Transaction::getDate() const
{
    return date;
}

void Transaction::setDate(const QDate &newDate)
{
    date = newDate;
}

const QString &Transaction::getPaymentMethod() const
{
    return paymentMethod;
}

void Transaction::setPaymentMethod(const QString &newPaymentMethod)
{
    paymentMethod = newPaymentMethod;
}

double Transaction::getAmount() const
{
    return amount;
}

void Transaction::setAmount(double newAmount)
{
    amount = newAmount;
}

Transaction::Transaction(int id, const QString &type, const QString &category, const QDate &date, const QString &paymentMethod, double amount) : id(id),
    type(type),
    category(category),
    date(date),
    paymentMethod(paymentMethod),
    amount(amount)
{}
