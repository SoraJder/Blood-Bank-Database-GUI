#include "searchpatient.h"
#include "ui_searchpatient.h"
#include "homepage.h"
#include <QMessageBox>

SearchPatient::SearchPatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchPatient)
{
    ui->setupUi(this);
     this->setFixedSize(1064,631);
}

SearchPatient::~SearchPatient()
{
    delete ui;
}

void SearchPatient::on_tableView_clicked(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    if(isOpenDatabase())
    {
    QSqlQuery query;
    query.prepare("Select * from Patient where patient_id='"+val+"' or first_name='"+val+"' or last_name='"+val+"' or"
     " email='"+val+"' or contact='"+val+"' or bloodGroup='"+val+"' or quantity='"+val+"' or gender='"+val+"';");
    if(query.exec())
    {
        while(query.next())
       {
        ui->lineEdit_firstName->setText(query.value(1).toString());
         ui->lineEdit_lastName->setText(query.value(2).toString());
         ui->lineEdit_email->setText(query.value(3).toString());
         ui->lineEdit_contact->setText(query.value(4).toString());
         ui->lineEdit_bloodGroup->setText(query.value(5).toString());
         ui->lineEdit_quantity->setText(query.value(6).toString());
         ui->lineEdit_gender->setText(query.value(7).toString());
        }
    }
    else
    {
        QMessageBox msgBox;
        QPalette palette;
        palette.setColor(QPalette::Background,Qt::white);
        msgBox.setPalette(palette);
        msgBox.setText("Something went wrong :(");
    }
    closeDatabase();
    }

}


void SearchPatient::on_pushButton_loadTable_clicked()
{
    ui->lineEdit_firstName->setText("");
     ui->lineEdit_lastName->setText("");
     ui->lineEdit_email->setText("");
     ui->lineEdit_contact->setText("");
     ui->lineEdit_bloodGroup->setText("");
     ui->lineEdit_quantity->setText("");
     ui->lineEdit_gender->setText("");

    if(isOpenDatabase())
    {
        if(ui->lineEdit_search->text().isEmpty())
        {
            QSqlQuery querry;
        querry.prepare("Select * from Patient;");
        if(querry.exec())
        {
            QSqlQueryModel * modal=new QSqlQueryModel();
            modal->setQuery(querry);
            ui->tableView->setModel(modal);
            qDebug()<<(modal->rowCount());
        }
        }
        else
        {
            QString category=ui->comboBox_categorySearch->currentText();
            QString personToSearch=ui->lineEdit_search->text();

             QSqlQuery *querry=new QSqlQuery(bloodBank);

            if(category=="patient_id")
            {
                querry->prepare("Select * from Patient WHERE patient_id ='"+personToSearch+"'");
            }
            else if(category=="first_name")
            {
                 querry->prepare("Select * from Patient WHERE first_name ='"+personToSearch+"'");
            }
            else if(category=="last_name")
            {
                 querry->prepare("Select * from Patient WHERE last_name ='"+personToSearch+"'");
            }
            else if(category=="email")
            {
                 querry->prepare("Select * from Patient WHERE email ='"+personToSearch+"'");
            }
            else if(category=="contact")
            {
                 querry->prepare("Select * from Patient WHERE contact ='"+personToSearch+"'");
            }
            else if(category=="bloodGroup")
            {
                 querry->prepare("Select * from Patient WHERE bloodGroup ='"+personToSearch+"'");
            }
            else
            {
                 querry->prepare("Select * from Patient WHERE gender='"+personToSearch+"'");
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
        }
         closeDatabase();
    }
}


void SearchPatient::on_pushButton_donate_clicked()
{
    QMessageBox msgBox;
    QPalette palette;
    palette.setColor(QPalette::Background,Qt::white);
    msgBox.setPalette(palette);
    if(ui->lineEdit_firstName->text().isEmpty())
    {
        msgBox.setText("You didn't select any data from table!");
        msgBox.exec();
    }
    else
    {
        if(isOpenDatabase())
        {
            QSqlQuery *query=new QSqlQuery(bloodBank);
            QString bloodGroup=ui->lineEdit_bloodGroup->text();
            query->prepare("Select * from BloodStock where bloodGroup='"+bloodGroup+"';");
            if(query->exec())
            {
                int quantityBloodStock;
                while(query->next())
                {
                    quantityBloodStock=query->value(1).toInt();
                }
                int quantityPatient=ui->lineEdit_quantity->text().toInt();
                if(quantityBloodStock-quantityPatient<0)
                {
                    msgBox.setText("There is not enough blood :(");
                    msgBox.exec();
                }
                else
                {
                    int newBloodStockQuantity=quantityBloodStock-quantityPatient;
                    QString bloodGroup=ui->lineEdit_bloodGroup->text();
                    QSqlQuery *query2=new QSqlQuery(bloodBank);
                    QSqlQuery *query3=new QSqlQuery(bloodBank);

                    query2->prepare("UPDATE BloodStock set quantity='"+QString::number(newBloodStockQuantity)+"' where bloodGroup='"+bloodGroup+"'");
                    query3->prepare("Delete from Patient where contact='"+ui->lineEdit_contact->text()+"' and first_name='"+ui->lineEdit_firstName->text()+"'"
                    "and last_name='"+ui->lineEdit_lastName->text()+"';");

                    if(query2->exec() && query3->exec())
                    {
                         msgBox.setText("Was successfully donated to "+ ui->lineEdit_lastName->text() +" "+ui->lineEdit_firstName->text()+" :)");
                         msgBox.exec();


                         QSqlQuery querry;
                     querry.prepare("Select * from Patient;");
                     if(querry.exec())
                     {
                         QSqlQueryModel * modal=new QSqlQueryModel();
                         modal->setQuery(querry);
                         ui->tableView->setModel(modal);
                         qDebug()<<(modal->rowCount());
                     }
                    }
                    else
                    {
                        msgBox.setText("Something went wrong :(");
                        msgBox.exec();
                    }

                }

            }
            else
            {
                msgBox.setText("Something went wrong :(");
                msgBox.exec();
            }

            closeDatabase();
        }
    }

}


void SearchPatient::on_pushButton_back_clicked()
{
    HomePage *menu=new HomePage();
    menu->show();
    this->hide();
}

bool SearchPatient::isOpenDatabase()
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

void SearchPatient::closeDatabase()
{
    bloodBank.close();
    bloodBank.removeDatabase(QSqlDatabase::defaultConnection);

}

