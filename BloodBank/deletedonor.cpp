#include "deletedonor.h"
#include "ui_deletedonor.h"
#include "homepage.h"
#include <QMessageBox>
#include <QDebug>
DeleteDonor::DeleteDonor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeleteDonor)
{
    ui->setupUi(this);
    canBeDelete=false;

    this->setFixedSize(803,425);
}

DeleteDonor::~DeleteDonor()
{
    delete ui;

}

void DeleteDonor::on_pushButton_searchId_clicked()
{
    if(isOpenDatabase())
    {
        QString search=ui->lineEdit_search->text();
        QSqlQueryModel queryModel;
        queryModel.setQuery("SELECT * FROM Donor WHERE donor_id='"+search+"';");
        if(queryModel.rowCount()==0)
        {
            QMessageBox msgBox;
            msgBox.warning(this,"Warning!","Donor doesn't exist!");
            canBeDelete=false;
        }
        else
        {
            ui->lineEdit_firstName->setText(queryModel.record(0).field(1).value().toString());
            ui->lineEdit_lastName->setText(queryModel.record(0).field(2).value().toString());
            ui->lineEdit_email->setText(queryModel.record(0).field(3).value().toString());
            ui->lineEdit_contact->setText(queryModel.record(0).field(4).value().toString());
            ui->lineEdit_bloodGroup->setText(queryModel.record(0).field(5).value().toString());
            ui->lineEdit_gender->setText(queryModel.record(0).field(6).value().toString());
            canBeDelete=true;
        }
        closeDatabase();
    }

}


void DeleteDonor::on_pushButton_back_clicked()
{
    HomePage *menu=new HomePage();
    menu->show();
    this->hide();
}


void DeleteDonor::on_pushButton_delete_clicked()
{
   if(isOpenDatabase())
   {
       QString donorId=ui->lineEdit_search->text();
       if(donorId.isEmpty())
       {
           QMessageBox msgBox;
           msgBox.warning(this,"Warning!","Search bar is empty!");
       }
       else
       {
            if(!canBeDelete)
            {
                QMessageBox msgBox;
                msgBox.warning(this,"Warning!","This donor doesn't exist anymore!");
                ui->lineEdit_firstName->clear();
                ui->lineEdit_lastName->clear();
                ui->lineEdit_email->clear();
                ui->lineEdit_contact->clear();
                ui->lineEdit_bloodGroup->clear();
                ui->lineEdit_gender->clear();
            }
            else
            {
                canBeDelete=false;
                QSqlQuery query;
                query.exec("Delete from Donor where donor_id='"+donorId+"';");
                ui->lineEdit_firstName->clear();
                ui->lineEdit_lastName->clear();
                ui->lineEdit_email->clear();
                ui->lineEdit_contact->clear();
                ui->lineEdit_bloodGroup->clear();
                ui->lineEdit_gender->clear();
                ui->lineEdit_search->clear();

                QMessageBox msgBox;
                msgBox.setText("Donor deleted");
                msgBox.exec();
            }
       }
       closeDatabase();
   }
}

bool DeleteDonor::isOpenDatabase()
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

void DeleteDonor::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}

