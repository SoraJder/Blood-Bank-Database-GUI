#include "newpatient.h"
#include "ui_newpatient.h"
#include "homepage.h"
#include <QMessageBox>
#include <regex>

NewPatient::NewPatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewPatient)
{
    ui->setupUi(this);
    this->setFixedSize(800,462);
}

NewPatient::~NewPatient()
{
    delete ui;
}

void NewPatient::on_pushButton_back_clicked()
{
    HomePage *menu=new HomePage();
    menu->show();
    this->hide();
}


void NewPatient::on_pushButton_addPatient_clicked()
{
    QString firstName=ui->lineEdit_firstName->text();
    QString lastName=ui->lineEdit_lastName->text();
    QString email=ui->lineEdit_email->text();
    QString contact=ui->lineEdit_contact->text();
    QString bloodGroup=ui->comboBox_bloodGroup->currentText();
    QString gender=ui->comboBox_gender->currentText();
    QString quantity=ui->lineEdit_quantity->text();


       QMessageBox msgBox;
       QPalette palette;
       palette.setColor(QPalette::Background,Qt::white);
       msgBox.setPalette(palette);
    if(firstName.isEmpty() || lastName.isEmpty()|| email.isEmpty()|| contact.isEmpty()||
            bloodGroup.isEmpty()||gender.isEmpty()|| quantity.isEmpty())
    {

        msgBox.warning(this,"Warning","Not all fields are completed!");
    }
    else if(!isEmailValid(email.toStdString()))
    {

        msgBox.warning(this,"Warning","The email is not valid!");
    }
    else if(contact.size()!=10)
    {

        msgBox.warning(this,"Warning","The contact is not valid!");
    }
    else if(quantity.toInt()<1)
    {

        msgBox.warning(this,"Warning","Invalid quantity!");
    }
    else
    {
        if(isOpenDatabase())
      {
        QSqlQuery querry;
        querry.prepare("INSERT INTO Patient (first_name,last_name,email,contact,bloodGroup,gender,quantity) VALUES"
                       " ('"+firstName+"','"+lastName+"','"+email+"','"+contact+"','"+bloodGroup+"','"+gender+"','"+quantity+"');");
        if(querry.exec())
        {
            msgBox.setText("The patient was successfully added!");
            msgBox.exec();
        }
        else
        {
            QMessageBox::critical(this,"Error",querry.lastError().text());
        }

        closeDatabase();
        ui->lineEdit_firstName->clear();
        ui->lineEdit_lastName->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_contact->clear();
        ui->lineEdit_quantity->clear();

      }
    }
}

bool NewPatient::isEmailValid(const std::string &email)
{
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool NewPatient::isOpenDatabase()
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

void NewPatient::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}

