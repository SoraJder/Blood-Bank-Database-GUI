#ifndef NEWPATIENT_H
#define NEWPATIENT_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class NewPatient;
}

class NewPatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewPatient(QWidget *parent = nullptr);
    ~NewPatient();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_addPatient_clicked();

private:
    Ui::NewPatient *ui;
    QSqlDatabase bloodBank;

     bool isEmailValid(const std::string&);
    bool isOpenDatabase();
    void closeDatabase();
};

#endif // NEWPATIENT_H
