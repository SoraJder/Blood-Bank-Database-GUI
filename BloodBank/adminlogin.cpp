#include "adminlogin.h"
#include "ui_adminlogin.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "newuser.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    this->setFixedSize(370,175);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_pushButton_clicked()
{
    if(ui->lineEdit_user->text().isEmpty() || ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.warning(this,"Warning!","The fields are not completed!");
    }
    else
    {
        QString user=ui->lineEdit_user->text();
        QString password=ui->lineEdit_password->text();

        if(isOpenDatabase())
        {
            QSqlQuery *querry = new QSqlQuery() ;
            if(querry->exec("SELECT * FROM Admin WHERE admin_name='"+user+"' AND password='"+password+"'"))
            {
                if(querry->next())
                {

                    NewUser *user=new NewUser();
                    user->show();
                    this->hide();

                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.critical(this,"Error!","Password or username is not correct!");

                }

            }
            closeDatabase();

        }
        else
        {
            QMessageBox msgBox;
            msgBox.critical(this,"Error!","Something went wrong :(");
        }

    }
}

bool AdminLogin::isOpenDatabase()
{
    bloodBank=QSqlDatabase::addDatabase("QSQLITE");
    bloodBank.setDatabaseName("C:/Users/Alina/Desktop/ProiectBD/BloodBank.db");
    if(!bloodBank.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Database connection failed :(");
        msgBox.exec();
        return false;
    }
    return true;
}

void AdminLogin::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}

