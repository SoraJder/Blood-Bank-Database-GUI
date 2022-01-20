#ifndef SEARCHDONOR_H
#define SEARCHDONOR_H

#include <QMainWindow>
#include "homepage.h"

namespace Ui {
class searchDonor;
}

class searchDonor : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchDonor(QWidget *parent = nullptr);
    ~searchDonor();

private slots:
    void on_pushButton_loadTable_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::searchDonor *ui;
    QSqlDatabase bloodBank;

    bool isOpenDatabase();
    void closeDatabase();
};

#endif // SEARCHDONOR_H
