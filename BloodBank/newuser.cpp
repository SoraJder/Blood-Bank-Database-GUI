#include "newuser.h"
#include "ui_newuser.h"
#include <QMessageBox>
#include <qsqlquery.h>
#include <regex>

NewUser::NewUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewUser)
{
    ui->setupUi(this);
    this->setFixedSize(760,370);
}

NewUser::~NewUser()
{
    delete ui;
}

void NewUser::on_pushButton_back_clicked()
{
    if(!ui->lineEdit_fullName->text().isEmpty()|| !ui->lineEdit_contact->text().isEmpty() || !ui->lineEdit_email->text().isEmpty()
            || !ui->lineEdit_password->text().isEmpty() || !ui->lineEdit_confirmPassword->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Some fields are completed.");
        msgBox.setInformativeText("Are you sure you want to go back?");
        msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret=msgBox.exec();

       if(ret==QMessageBox::Yes)
       {
           this->close();
       }

    }
    else
    {
        this->close();
    }
}


void NewUser::on_pushButton_addUser_clicked()
{


    if(ui->lineEdit_fullName->text().isEmpty()|| ui->lineEdit_contact->text().isEmpty() || ui->lineEdit_email->text().isEmpty()
            || ui->lineEdit_password->text().isEmpty() || ui->lineEdit_confirmPassword->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.warning(this,"Warning!","The fields are not completed!");
    }
    else
    {
        QString fullname=ui->lineEdit_fullName->text();
        QString contact=ui->lineEdit_contact->text();
        QString email=ui->lineEdit_email->text();
        QString password=ui->lineEdit_password->text();
        QString confirmPassword=ui->lineEdit_confirmPassword->text();

        if(!isEmailValid(email.toStdString()))
        {
            QMessageBox msgBox;
            msgBox.warning(this,"Warning!","Email is not valid!");
            return;
        }
        else if(password!=confirmPassword)
        {
            QMessageBox msgBox;
            msgBox.warning(this,"Warning!","Confirm password is not the same with the password!");
            return;
        }
        else
         {
            if(isOpenDatabase())
            {
                QSqlQuery *querry = new QSqlQuery;
                querry->prepare("INSERT INTO User (fullname,contact,email,password) VALUES"
                               " ('"+fullname+"','"+contact+"','"+email+"','"+password+"');");
                if(querry->exec())
                {
                    QMessageBox msgBox;
                    msgBox.setText("The User was successfully added!");
                    msgBox.exec();
                    this->close();
                }
                else
                {
                     QMessageBox::critical(this,"Error","Something went bad");
                }

                ui->lineEdit_confirmPassword->clear();
                ui->lineEdit_contact->clear();
                ui->lineEdit_email->clear();
                ui->lineEdit_fullName->clear();
                ui->lineEdit_password->clear();

                closeDatabase();
            }
          }

}

}

bool NewUser::isEmailValid(const std::string &email)
{
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool NewUser::isOpenDatabase()
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

void NewUser::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}

