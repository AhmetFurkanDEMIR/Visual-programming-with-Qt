#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QSqlTableModel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase Database;
    Database = QSqlDatabase::addDatabase("QSQLITE");
    Database.setDatabaseName("/home/demir/Quiz/database.db");

    if (!Database.open())
    {
        ui->statusbar->showMessage("Error, Veri tabanına bağlanılamadı X");
    }

    else{
        ui->statusbar->showMessage("Veri tabanına bağlanıldı!");
    }

    readd();


    QSqlTableModel *model;
    QSqlTableModel *model2;

    model = new QSqlTableModel();
    model->setTable("gecenler");
    ui->tableView->setModel(model);
    model->select();
    model2 = new QSqlTableModel();
    model2->setTable("kalanlar");
    ui->tableView_2->setModel(model2);
    model2->select();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readd(){

    int flag_run = 0;

    QSqlQuery query("SELECT ogr_id FROM gecenler");
    if(query.next()==false){
        flag_run=1;

    }

    if(flag_run==1){

        QFile file("/home/demir/Quiz/ogrenciler.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }

        QTextStream in(&file);
        QString line;

        while (!in.atEnd()) {

            line = in.readLine();

            QStringList temp;
            temp = line.split(" ");

            int a = temp.at(3).toInt()*0.4 + temp.at(4).toInt()*0.6;

            if(a>=60){

                query.prepare("INSERT INTO gecenler(ogr_id, ogr_ad, ogr_soyad, gecme_notu) "
                                              "VALUES (?, ?, ?, ?)");

                query.bindValue(0, temp.at(0).toInt());
                query.bindValue(1, temp.at(1));
                query.bindValue(2, temp.at(2));
                query.bindValue(3, a);
                query.exec();

            }

            else{

                query.prepare("INSERT INTO kalanlar(ogr_id, ogr_ad, ogr_soyad, gecme_notu) "
                                              "VALUES (?, ?, ?, ?)");

                query.bindValue(0, temp.at(0).toInt());
                query.bindValue(1, temp.at(1));
                query.bindValue(2, temp.at(2));
                query.bindValue(3, a);
                query.exec();

            }

        }

    }


}

void MainWindow::on_pushButton_clicked()
{

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()=="" || ui->lineEdit_4->text()==""){

        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        return;
    }

    else if(ui->lineEdit_4->text().toInt()>=60){

        QSqlQuery query;
        query.prepare("INSERT INTO gecenler(ogr_id, ogr_ad, ogr_soyad, gecme_notu) "
                                      "VALUES (?, ?, ?, ?)");

        query.bindValue(0, ui->lineEdit->text());
        query.bindValue(1, ui->lineEdit_2->text());
        query.bindValue(2, ui->lineEdit_3->text());
        query.bindValue(3, ui->lineEdit_4->text());
        query.exec();

    }

    else{

        QSqlQuery query;
        query.prepare("INSERT INTO kalanlar(ogr_id, ogr_ad, ogr_soyad, gecme_notu) "
                                      "VALUES (?, ?, ?, ?)");

        query.bindValue(0, ui->lineEdit->text());
        query.bindValue(1, ui->lineEdit_2->text());
        query.bindValue(2, ui->lineEdit_3->text());
        query.bindValue(3, ui->lineEdit_4->text());
        query.exec();

    }

    QSqlTableModel *model;
    QSqlTableModel *model2;

    model = new QSqlTableModel();
    model->setTable("gecenler");
    ui->tableView->setModel(model);
    model->select();
    model2 = new QSqlTableModel();
    model2->setTable("kalanlar");
    ui->tableView_2->setModel(model2);
    model2->select();

}

