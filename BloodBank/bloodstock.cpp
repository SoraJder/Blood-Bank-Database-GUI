#include "bloodstock.h"
#include "ui_bloodstock.h"
#include "homepage.h"
#include <QMessageBox>

BloodStock::BloodStock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BloodStock)
{
    ui->setupUi(this);
}

BloodStock::~BloodStock()
{
    delete ui;
}

void BloodStock::on_pushButton_loadTable_clicked()
{
    if(isOpenDatabase())
    {QSqlQuery querry;
    querry.prepare("Select * from BloodStock;");
    if(querry.exec())
   { QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery(querry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());
    }
    closeDatabase();
    }
}


void BloodStock::on_pushButton_back_clicked()
{
    HomePage *menu=new HomePage();
    menu->show();
    this->hide();
}

bool BloodStock::isOpenDatabase()
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

void BloodStock::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);
}

