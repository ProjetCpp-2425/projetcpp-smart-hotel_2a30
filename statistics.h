#ifndef STATISTICS_H
#define STATISTICS_H
#include<QVector>

class Statistics
{
    public:
        Statistics();

         QVector<double> incomes;
         QVector<double> expenses;
         QVector<double> profitLoss;
         int year;
};

#endif // STATISTICS_H
