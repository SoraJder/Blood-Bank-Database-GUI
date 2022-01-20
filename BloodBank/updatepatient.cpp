#include "updatepatient.h"
#include "ui_updatepatient.h"
#include "homepage.h"
#include <QMessageBox>

UpdatePatient::UpdatePatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdatePatient)
{
    ui->setupUi(this);
    updatePatient=false;
    this->setFixedSize(803,425);
}

UpdatePatient::~UpdatePatient()
{
    delete ui;
}

void UpdatePatient::on_pushButton_back_clicked()
{
    HomePage *menu=new HomePage();
    menu->show();
    this->hide();
}


void UpdatePatient::on_pushButton_update_clicked()
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
            if(!updatePatient)
            {
                QMessageBox msgBox;
                msgBox.warning(this,"Warning!","This patient doesn't exist anymore!");
                ui->lineEdit_firstName->clear();
                ui->lineEdit_lastName->clear();
                ui->lineEdit_email->clear();
                ui->lineEdit_contact->clear();
                ui->lineEdit_bloodGroup->clear();
                ui->lineEdit_gender->clear();
                ui->lineEdit_quantity->clear();
            }
            else
            {
                updatePatient=false;
                QString firstName= ui->lineEdit_firstName->text();
                QString lastName= ui->lineEdit_lastName->text();
                QString email=ui->lineEdit_email->text();
                QString contact=ui->lineEdit_contact->text();
                QString bloodGroup=ui->lineEdit_bloodGroup->text();
                QString gender=ui->lineEdit_gender->text();
                QString quantity=ui->lineEdit_quantity->text();

                QSqlQuery query;
                query.prepare("UPDATE Patient set first_name='"+firstName+"', last_name='"+lastName+"',email='"+email+"',contact='"+contact+"',"
                           "bloodGroup='"+bloodGroup+"',quantity='"+quantity+"', gender='"+gender+"' WHERE patient_id='"+searchBar+"';");
                if(query.exec())
                {
                    QMessageBox msgBox;
                    msgBox.setText("Patient updated");
                    msgBox.exec();

                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.warning(this,"Warning!","Something went wrong!");
                }

            }
        }

        closeDatabase();
    }
}


void UpdatePatient::on_pushButton_searchId_clicked()
{
    if(isOpenDatabase())
    {
        QString search=ui->lineEdit_search->text();
        QSqlQueryModel queryModel;
        queryModel.setQuery("SELECT * FROM Patient WHERE patient_id='"+search+"';");
        if(queryModel.rowCount()==0)
        {
            QMessageBox msgBox;
            msgBox.warning(this,"Warning!","Patient doesn't exist!");
            ui->lineEdit_firstName->clear();
            ui->lineEdit_lastName->clear();
            ui->lineEdit_email->clear();
            ui->lineEdit_contact->clear();
            ui->lineEdit_bloodGroup->clear();
            ui->lineEdit_gender->clear();
            ui->lineEdit_quantity->clear();
            updatePatient=false;

        }
        else
        {
            ui->lineEdit_firstName->setText(queryModel.record(0).field(1).value().toString());
            ui->lineEdit_lastName->setText(queryModel.record(0).field(2).value().toString());
            ui->lineEdit_email->setText(queryModel.record(0).field(3).value().toString());
            ui->lineEdit_contact->setText(queryModel.record(0).field(4).value().toString());
            ui->lineEdit_bloodGroup->setText(queryModel.record(0).field(5).value().toString());
            ui->lineEdit_gender->setText(queryModel.record(0).field(7).value().toString());
            ui->lineEdit_quantity->setText(queryModel.record(0).field(6).value().toString());
            updatePatient=true;

        }
        closeDatabase();
    }
}

bool UpdatePatient::isOpenDatabase()
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

void UpdatePatient::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}

