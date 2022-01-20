#ifndef DELETEDONOR_H
#define DELETEDONOR_H

#include <QMainWindow>
#include "homepage.h"

namespace Ui {
class DeleteDonor;
}

class DeleteDonor : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeleteDonor(QWidget *parent = nullptr);
    ~DeleteDonor();

private slots:
    void on_pushButton_searchId_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::DeleteDonor *ui;
     QSqlDatabase bloodBank;
     bool canBeDelete;

    bool isOpenDatabase();
    void closeDatabase();
};

#endif // DELETEDONOR_H
