#include "searchdonor.h"
#include "ui_searchdonor.h"
#include <QMessageBox>

searchDonor::searchDonor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchDonor)
{
    ui->setupUi(this);
    this->setFixedSize(1050,610);
}

searchDonor::~searchDonor()
{
    delete ui;
}

void searchDonor::on_pushButton_loadTable_clicked()
{
    if(isOpenDatabase())
    {
        QString category=ui->comboBox_categorySearch->currentText();
        QString personToSearch=ui->lineEdit_search->text();

        QSqlQuery *querry=new QSqlQuery(bloodBank);

        if(category=="donor_id")
        {
            querry->prepare("Select * from Donor WHERE donor_id ='"+personToSearch+"'");
        }
        else if(category=="first_name")
        {
             querry->prepare("Select * from Donor WHERE first_name ='"+personToSearch+"'");
        }
        else if(category=="last_name")
        {
             querry->prepare("Select * from Donor WHERE last_name ='"+personToSearch+"'");
        }
        else if(category=="email")
        {
             querry->prepare("Select * from Donor WHERE email ='"+personToSearch+"'");
        }
        else if(category=="contact")
        {
             querry->prepare("Select * from Donor WHERE contact ='"+personToSearch+"'");
        }
        else if(category=="bloodGroup")
        {
             querry->prepare("Select * from Donor WHERE bloodGroup ='"+personToSearch+"'");
        }
        else if(category=="gender")
        {
             querry->prepare("Select * from Donor WHERE gender='"+personToSearch+"'");
        }
        else
        {
             querry->prepare("Select * from Donor");
        }

        if(querry->exec())
        {
        QSqlQueryModel * modal=new QSqlQueryModel();
        modal->setQuery(*querry);
        ui->tableView->setModel(modal);
        qDebug()<<(modal->rowCount());
        }
        else
        {
            QMessageBox msgBox;
            msgBox.warning(this,"Warning","Something doesn't work!");
        }
       closeDatabase();
    }

}

bool searchDonor::isOpenDatabase()
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

void searchDonor::closeDatabase()
{
       bloodBank.close();
       bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}


void searchDonor::on_pushButton_back_clicked()
{
    HomePage *menu=new HomePage();
    menu->show();
    this->hide();
}
