#ifndef UPDATEDONOR_H
#define UPDATEDONOR_H

#include <QMainWindow>
#include "homepage.h"

namespace Ui {
class UpdateDonor;
}

class UpdateDonor : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdateDonor(QWidget *parent = nullptr);
    ~UpdateDonor();

private slots:
    void on_pushButton_searchId_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_update_clicked();

private:
    Ui::UpdateDonor *ui;
    QSqlDatabase bloodBank;
    bool updateDonor;

   bool isOpenDatabase();
   void closeDatabase();
};

#endif // UPDATEDONOR_H
