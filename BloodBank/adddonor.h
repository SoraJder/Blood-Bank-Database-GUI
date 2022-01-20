#ifndef ADDDONOR_H
#define ADDDONOR_H

#include <QMainWindow>
#include "homepage.h"


namespace Ui {
class AddDonor;
}

class AddDonor : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddDonor(QWidget *parent = nullptr);
    ~AddDonor();

private slots:


    void on_pushButton_back_clicked();
    void on_pushButton_addDonor_clicked();

private:
    Ui::AddDonor *ui;
     QSqlDatabase bloodBank;

    bool isEmailValid(const std::string&);
    bool isOpenDatabase();
    void closeDatabase();
};

#endif // ADDDONOR_H
