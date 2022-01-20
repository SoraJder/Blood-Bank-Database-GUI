#include "login.h"
#include "homepage.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(477,515);
    bloodBank=QSqlDatabase::addDatabase("QSQLITE");
    bloodBank.setDatabaseName("C:/Users/Alina/Desktop/ProiectBD/BloodBank.db");
    if(!bloodBank.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Database connection failed :(");
        msgBox.exec();
    }
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_login_clicked()
{
    if(bloodBank.open())
    {

    QString email=ui->lineEdit_email->text();
    QString password=ui->lineEdit_password->text();
    QSqlQuery query;

    if(query.exec("SELECT * FROM User WHERE email='"+email+"' AND password='"+password+"'"))
    {
        if(query.next())
        {

            HomePage *homePage=new HomePage();
            homePage->show();
            this->hide();
            bloodBank.close();
            bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.critical(this,"Error!","Password or username is not correct!");

        }

    }
    }
}

