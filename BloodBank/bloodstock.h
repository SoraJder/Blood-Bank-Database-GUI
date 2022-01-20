#ifndef BLOODSTOCK_H
#define BLOODSTOCK_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class BloodStock;
}

class BloodStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit BloodStock(QWidget *parent = nullptr);
    ~BloodStock();

private slots:
    void on_pushButton_loadTable_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::BloodStock *ui;
     QSqlDatabase bloodBank;

    bool isOpenDatabase();
    void closeDatabase();
};

#endif // BLOODSTOCK_H
