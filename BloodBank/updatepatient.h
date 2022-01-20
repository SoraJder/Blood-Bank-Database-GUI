#ifndef UPDATEPATIENT_H
#define UPDATEPATIENT_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class UpdatePatient;
}

class UpdatePatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdatePatient(QWidget *parent = nullptr);
    ~UpdatePatient();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_searchId_clicked();

private:
    Ui::UpdatePatient *ui;
    QSqlDatabase bloodBank;
    bool updatePatient;

   bool isOpenDatabase();
   void closeDatabase();
};

#endif // UPDATEPATIENT_H
