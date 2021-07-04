#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include "clickablelabel.h"
#include "dersislemleri.h"
#include "ogrenciislemleri.h"
#include "notislemleri.h"

/*

CREATE TABLE "dersler" (
    "ders_kodu"	INTEGER NOT NULL UNIQUE,
    "ders_adi"	TEXT,
    PRIMARY KEY("ders_kodu")
);

CREATE TABLE "notlar" (
    "ogr_no"	INTEGER,
    "ders_kodu"	INTEGER,
    "vize_not"	INTEGER,
    "final_not"	INTEGER,
    "geçme_notu"	INTEGER
);

CREATE TABLE "öğrenci" (
    "ogr_no"	INTEGER NOT NULL UNIQUE,
    "ogr_ad"	TEXT,
    "ogr_soyad"	TEXT,
    PRIMARY KEY("ogr_no" AUTOINCREMENT)
);

CREATE TABLE "sqlite_sequence" (
    "name"	,
    "seq"
);


*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(664, 390);
    this->move(382, 134);

    QPixmap pix1(":/Images/images/ogr.jpg");
    ClickableLabel *label_ogr = new ClickableLabel(this);
    label_ogr->setPixmap(pix1.scaled(133,133,Qt::KeepAspectRatio));
    label_ogr->move(30,110);
    label_ogr->setFixedWidth(161);
    label_ogr->setFixedHeight(161);
    label_ogr->show();

    ClickableLabel *label_ogr_text = new ClickableLabel(this);
    label_ogr_text->setText(" Öğrenci İşlemleri");
    label_ogr_text->move(30,270);
    label_ogr_text->setFixedWidth(161);
    label_ogr_text->setFixedHeight(31);
    label_ogr_text->setStyleSheet("font-weight: bold; color: black");
    label_ogr_text->show();

    connect(label_ogr, SIGNAL(clicked()), this, SLOT(ogrenci_islemleri()));
    connect(label_ogr_text, SIGNAL(clicked()), this, SLOT(ogrenci_islemleri()));



    QPixmap pix2(":/Images/images/ders.jpg");
    ClickableLabel *label_ders = new ClickableLabel(this);
    label_ders->setPixmap(pix2.scaled(133,133,Qt::KeepAspectRatio));
    label_ders->move(258,110);
    label_ders->setFixedWidth(161);
    label_ders->setFixedHeight(161);
    label_ders->show();

    ClickableLabel *label_ders_text = new ClickableLabel(this);
    label_ders_text->setText("   Ders İşlemleri");
    label_ders_text->move(258,270);
    label_ders_text->setFixedWidth(161);
    label_ders_text->setFixedHeight(31);
    label_ders_text->setStyleSheet("font-weight: bold; color: black");
    label_ders_text->show();

    connect(label_ders, SIGNAL(clicked()), this, SLOT(ders_islemleri()));
    connect(label_ders_text, SIGNAL(clicked()), this, SLOT(ders_islemleri()));



    QPixmap pix3(":/Images/images/notlar.jpg");
    ClickableLabel *label_notlar = new ClickableLabel(this);
    label_notlar->setPixmap(pix3.scaled(150,150,Qt::KeepAspectRatio));
    label_notlar->move(480,110);
    label_notlar->setFixedWidth(161);
    label_notlar->setFixedHeight(161);
    label_notlar->show();

    ClickableLabel *label_not_text = new ClickableLabel(this);
    label_not_text->setText("      Not İşlemleri");
    label_not_text->move(480,270);
    label_not_text->setFixedWidth(161);
    label_not_text->setFixedHeight(31);
    label_not_text->setStyleSheet("font-weight: bold; color: black");
    label_not_text->show();

    connect(label_notlar, SIGNAL(clicked()), this, SLOT(not_islemleri()));
    connect(label_not_text, SIGNAL(clicked()), this, SLOT(not_islemleri()));


    QSqlDatabase Database;
    Database = QSqlDatabase::addDatabase("QSQLITE");
    Database.setDatabaseName("C:/Users/demir/Desktop/Homework/database.db");

    if (!Database.open())
    {
        ui->statusbar->showMessage("Error, Veri tabanına bağlanılamadı X");
    }

    else{
        ui->statusbar->showMessage("Veri tabanına bağlanıldı!");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ogrenci_islemleri(){

    hide();
    OgrenciIslemleri *dialog = new OgrenciIslemleri();
    dialog->show();
}

void MainWindow::ders_islemleri(){

    hide();
    DersIslemleri *dialog = new DersIslemleri();
    dialog->show();

}

void MainWindow::not_islemleri(){

    hide();
    NotIslemleri *dialog = new NotIslemleri();
    dialog->show();
}
