#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = nullptr);
    ~AdminLogin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AdminLogin *ui;
    QSqlDatabase bloodBank;


   bool isOpenDatabase();
   void closeDatabase();
};

#endif // ADMINLOGIN_H
