#include "adddonor.h"
#include "ui_adddonor.h"
#include <regex>

#include <QMessageBox>

AddDonor::AddDonor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddDonor)
{
    ui->setupUi(this);
    this->setFixedSize(711,371);

}

AddDonor::~AddDonor()
{
    delete ui;
}

void AddDonor::on_pushButton_back_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to go back to menu?");
    msgBox.setInformativeText("If you go back the new data will not be saved!");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

   if(msgBox.exec()==QMessageBox::Yes)
   {
    HomePage *back=new HomePage();
    back->show();
    this->hide();
    }
}


void AddDonor::on_pushButton_addDonor_clicked()
{
    QString firstName=ui->lineEdit_firstName->text();
    QString lastName=ui->lineEdit_lastName->text();
    QString email=ui->lineEdit_email->text();
    QString contact=ui->lineEdit_contact->text();
    QString bloodGroup=ui->comboBox_bloodGroup->currentText();
    QString gender=ui->comboBox_gender->currentText();

    if(firstName.isEmpty() || lastName.isEmpty()|| email.isEmpty()|| contact.isEmpty()||
            bloodGroup.isEmpty()||gender.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.warning(this,"Warning","Not all fields are completed!");
    }
    else if(!isEmailValid(email.toStdString()))
    {
        QMessageBox msgBox;
        msgBox.warning(this,"Warning","The email is not valid!");
    }
    else if(contact.size()!=10)
    {
        QMessageBox msgBox;
        msgBox.warning(this,"Warning","The contact is not valid!");
    }
    else
    {
        if(isOpenDatabase())
      {
        QSqlQuery querry;
        querry.prepare("INSERT INTO Donor (first_name,last_name,email,contact,bloodGroup,gender) VALUES"
                       " ('"+firstName+"','"+lastName+"','"+email+"','"+contact+"','"+bloodGroup+"','"+gender+"');");
        if(querry.exec())
        {
            /* fiecare donator va dona cate trei pungulite de sange
            */
           QSqlQuery querryBlood;
            querryBlood.prepare("UPDATE BloodStock set quantity=quantity+2 where bloodGroup='"+bloodGroup+"';");
            querryBlood.exec();
            QMessageBox msgBox;
            msgBox.setText("The Donor was successfully added!");
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

      }
    }


}

bool AddDonor::isEmailValid(const std::string &email)
{
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool AddDonor::isOpenDatabase()
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

void AddDonor::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}



