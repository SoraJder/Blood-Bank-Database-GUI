#ifndef SEARCHPATIENT_H
#define SEARCHPATIENT_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class SearchPatient;
}

class SearchPatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchPatient(QWidget *parent = nullptr);
    ~SearchPatient();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_loadTable_clicked();

    void on_pushButton_donate_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::SearchPatient *ui;
    QSqlDatabase bloodBank;

    bool isOpenDatabase();
    void closeDatabase();
};

#endif // SEARCHPATIENT_H
