#ifndef STAT_H
#define STAT_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class stat;
}

class stat : public QDialog
{
    Q_OBJECT

public:
    explicit stat(QWidget *parent = nullptr);
    ~stat();

    void showStatistics();

private:
    Ui::stat *ui;
};

#endif // STAT_H
