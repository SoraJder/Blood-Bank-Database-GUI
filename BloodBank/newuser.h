#ifndef NEWUSER_H
#define NEWUSER_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class NewUser;
}

class NewUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewUser(QWidget *parent = nullptr);
    ~NewUser();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_addUser_clicked();

private:
    Ui::NewUser *ui;

    QSqlDatabase bloodBank;

   bool isEmailValid(const std::string&);
   bool isOpenDatabase();
   void closeDatabase();
};

#endif // NEWUSER_H
