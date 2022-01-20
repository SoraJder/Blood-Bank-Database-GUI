#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class HomePage;
}

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();
private slots:


    void on_pushButton_addDonor_clicked();

    void on_pushButton_deleteDonor_clicked();

    void on_pushButton_searchDonor_clicked();

    void on_pushButto_logOut_clicked();

    void on_pushButton_updateDonor_clicked();

    void on_pushButton_bloodStock_clicked();

    void on_pushButton_addPatient_clicked();

    void on_pushButton_searchPatient_clicked();

    void on_pushButton_updatePatient_clicked();

    void on_pushButto_createStaffAccount_clicked();

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
