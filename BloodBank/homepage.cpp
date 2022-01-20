#include "homepage.h"
#include "ui_homepage.h"
#include "login.h"
#include "adddonor.h"
#include "searchdonor.h"
#include "deletedonor.h"
#include "updatedonor.h"
#include "bloodstock.h"
#include"newpatient.h"
#include "searchpatient.h"
#include "updatepatient.h"
#include "adminlogin.h"

HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    this->setFixedSize(510,300);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_pushButton_addDonor_clicked()
{
    AddDonor* newDonor=new AddDonor();
    newDonor->show();
    this->hide();
}



void HomePage::on_pushButton_searchDonor_clicked()
{
    searchDonor* search=new searchDonor();
    search->show();
    this->hide();
}



void HomePage::on_pushButto_logOut_clicked()
{
    Login *logOut=new Login();
    logOut->show();
    this->hide();
}


void HomePage::on_pushButton_deleteDonor_clicked()
{
    DeleteDonor *deleteDonor=new DeleteDonor();
    deleteDonor->show();
    this->hide();
}


void HomePage::on_pushButton_updateDonor_clicked()
{
    UpdateDonor *updateDonor=new UpdateDonor();
    updateDonor->show();
    this->hide();
}


void HomePage::on_pushButton_bloodStock_clicked()
{
    BloodStock *stock=new BloodStock();
    stock->show();
    this->hide();
}


void HomePage::on_pushButton_addPatient_clicked()
{
    NewPatient *patient=new NewPatient();
    patient->show();
    this->hide();
}


void HomePage::on_pushButton_searchPatient_clicked()
{
    SearchPatient *patient=new SearchPatient();
    patient->show();
    this->hide();
}


void HomePage::on_pushButton_updatePatient_clicked()
{
    UpdatePatient *patient=new UpdatePatient();
    patient->show();
    this->hide();
}


void HomePage::on_pushButto_createStaffAccount_clicked()
{
    AdminLogin *admin=new AdminLogin();
    admin->show();
}

