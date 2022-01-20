#include "updatedonor.h"
#include "ui_updatedonor.h"
#include <QMessageBox>

UpdateDonor::UpdateDonor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateDonor)
{
    ui->setupUi(this);
    updateDonor=false;
    this->setFixedSize(803,425);
}

UpdateDonor::~UpdateDonor()
{
    delete ui;
}

void UpdateDonor::on_pushButton_searchId_clicked()
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
            ui->lineEdit_firstName->clear();
            ui->lineEdit_lastName->clear();
            ui->lineEdit_email->clear();
            ui->lineEdit_contact->clear();
            ui->lineEdit_bloodGroup->clear();
            ui->lineEdit_gender->clear();
            updateDonor=false;

        }
        else
        {
            ui->lineEdit_firstName->setText(queryModel.record(0).field(1).value().toString());
            ui->lineEdit_lastName->setText(queryModel.record(0).field(2).value().toString());
            ui->lineEdit_email->setText(queryModel.record(0).field(3).value().toString());
            ui->lineEdit_contact->setText(queryModel.record(0).field(4).value().toString());
            ui->lineEdit_bloodGroup->setText(queryModel.record(0).field(5).value().toString());
            ui->lineEdit_gender->setText(queryModel.record(0).field(6).value().toString());
            updateDonor=true;

        }
        closeDatabase();
    }
}


void UpdateDonor::on_pushButton_back_clicked()
{
    HomePage *menu=new HomePage();
    menu->show();
    this->hide();
}


void UpdateDonor::on_pushButton_update_clicked()
{
    if (isOpenDatabase())
    {
        QString searchBar=ui->lineEdit_search->text();

        if(searchBar.isEmpty())
        {
            QMessageBox msgBox;
            msgBox.warning(this,"Warning!","Search bar is empty!");
        }
       else
        {
            if(!updateDonor)
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
                updateDonor=false;
                QString firstName= ui->lineEdit_firstName->text();
                QString lastName= ui->lineEdit_lastName->text();
                QString email=ui->lineEdit_email->text();
                QString contact=ui->lineEdit_contact->text();
                QString bloodGroup=ui->lineEdit_bloodGroup->text();
                QString gender=ui->lineEdit_gender->text();

                QSqlQuery query;
                query.exec("UPDATE Donor set first_name='"+firstName+"', last_name='"+lastName+"',email='"+email+"',contact='"+contact+"',"
                           "bloodGroup='"+bloodGroup+"', gender='"+gender+"' WHERE donor_id='"+searchBar+"';");
                    QMessageBox msgBox;
                    msgBox.setText("Donor updated");
                    msgBox.exec();

            }
        }

        closeDatabase();
    }
}

bool UpdateDonor::isOpenDatabase()
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

void UpdateDonor::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}


