#ifndef EXPENSE_H
#define EXPENSE_H
#include<string>
#include<QDate>
using namespace std;

class Expense
{
private:
    int idexpense;
    QString status;
    int priority;
    QDate due_date;
    double remain_budget;
    QString note;
    QString title;
    double balance;

public:
    Expense();
    int getIdexpense() const;
    void setIdexpense(int newIdexpense);
    const QString &getStatus() const;
    void setStatus(const QString &newStatus);
    int getPriority() const;
    void setPriority(int newPriority);
    const QDate &getDue_date() const;
    void setDue_date(const QDate &newDue_date);
    double getRemain_budget() const;
    void setRemain_budget(double newRemain_budget);
    const QString &getNote() const;
    void setNote(const QString &newNote);
    const QString &getTitle() const;
    void setTitle(const QString &newTitle);
    double getBalance() const;
    void setBalance(double newBalance);
};

#endif // EXPENSE_H
