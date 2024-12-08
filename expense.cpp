#include "expense.h"

int Expense::getIdexpense() const
{
    return idexpense;
}

void Expense::setIdexpense(int newIdexpense)
{
    idexpense = newIdexpense;
}

const QString &Expense::getStatus() const
{
    return status;
}

void Expense::setStatus(const QString &newStatus)
{
    status = newStatus;
}

int Expense::getPriority() const
{
    return priority;
}

void Expense::setPriority(int newPriority)
{
    priority = newPriority;
}

const QDate &Expense::getDue_date() const
{
    return due_date;
}

void Expense::setDue_date(const QDate &newDue_date)
{
    due_date = newDue_date;
}

double Expense::getRemain_budget() const
{
    return remain_budget;
}

void Expense::setRemain_budget(double newRemain_budget)
{
    remain_budget = newRemain_budget;
}

const QString &Expense::getNote() const
{
    return note;
}

void Expense::setNote(const QString &newNote)
{
    note = newNote;
}

const QString &Expense::getTitle() const
{
    return title;
}

void Expense::setTitle(const QString &newTitle)
{
    title = newTitle;
}

double Expense::getBalance() const
{
    return balance;
}

void Expense::setBalance(double newBalance)
{
    balance = newBalance;
}

Expense::Expense()
{

}
