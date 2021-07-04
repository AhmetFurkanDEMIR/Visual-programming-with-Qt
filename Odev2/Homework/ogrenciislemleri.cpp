#include "ogrenciislemleri.h"
#include "ui_ogrenciislemleri.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "mainwindow.h"

OgrenciIslemleri::OgrenciIslemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OgrenciIslemleri)
{
    ui->setupUi(this);
    this->setFixedSize(664, 484);

    model = new QSqlQueryModel();
    model->setQuery("SELECT ogr_no, ogr_ad, ogr_soyad FROM öğrenci");
    model->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model->setHeaderData(1, Qt::Horizontal, tr("ogr_ad"));
    model->setHeaderData(1, Qt::Horizontal, tr("ogr_soyad"));
    ui->tableView->setModel(model);

    QItemSelectionModel *sm = ui->tableView->selectionModel();
    connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(selected(QModelIndex,QModelIndex)));
}

OgrenciIslemleri::~OgrenciIslemleri()
{
    delete ui;
}


void OgrenciIslemleri::selected(QModelIndex a,QModelIndex b){


    QModelIndex index = model->index(a.row(), 0, QModelIndex());
    QModelIndex index1 = model->index(a.row(), 1, QModelIndex());
    QModelIndex index2 = model->index(a.row(), 2, QModelIndex());
    secili_no = qPrintable(ui->tableView->model()->data(index).toString());
    secili_ad = qPrintable(ui->tableView->model()->data(index1).toString());
    secili_soyad = qPrintable(ui->tableView->model()->data(index2).toString());

    ui->lineEdit->setText(secili_no);
    ui->lineEdit_2->setText(secili_ad);
    ui->lineEdit_3->setText(secili_soyad);

}

// yeni kayit
void OgrenciIslemleri::on_pushButton_clicked()
{

    if(ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()==""){
        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO öğrenci(ogr_ad, ogr_soyad) "
                              "VALUES (?, ?)");

    query.bindValue(0, ui->lineEdit_2->text());
    query.bindValue(1, ui->lineEdit_3->text());
    query.exec();

    model = new QSqlQueryModel();
    model->setQuery("SELECT ogr_no, ogr_ad, ogr_soyad FROM öğrenci");
    model->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model->setHeaderData(1, Qt::Horizontal, tr("ogr_ad"));
    model->setHeaderData(1, Qt::Horizontal, tr("ogr_soyad"));
    ui->tableView->setModel(model);

    QItemSelectionModel *sm = ui->tableView->selectionModel();
    connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(selected(QModelIndex,QModelIndex)));

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");

    QMessageBox messageBox;
    messageBox.information(0,"Başarılı!","Ogrenci ekleme başarılı.");
}

// guncelle
void OgrenciIslemleri::on_pushButton_2_clicked()
{

    if(ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()==""){
        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        ui->lineEdit->setText(secili_no);
        ui->lineEdit_2->setText(secili_ad);
        ui->lineEdit_3->setText(secili_soyad);;

        return;
    }

    QSqlQuery query;

    query.prepare("UPDATE öğrenci SET ogr_ad = ?, ogr_soyad = ? WHERE ogr_no = ?");
    query.bindValue(0, ui->lineEdit_2->text());
    query.bindValue(1, ui->lineEdit_3->text());
    query.bindValue(2, secili_no);
    query.exec();

    model = new QSqlQueryModel();
    model->setQuery("SELECT ogr_no, ogr_ad, ogr_soyad FROM öğrenci");
    model->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model->setHeaderData(1, Qt::Horizontal, tr("ogr_ad"));
    model->setHeaderData(1, Qt::Horizontal, tr("ogr_soyad"));
    ui->tableView->setModel(model);

    QItemSelectionModel *sm = ui->tableView->selectionModel();
    connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(selected(QModelIndex,QModelIndex)));

    QMessageBox messageBox;
    messageBox.information(0,"Başarılı!","Ogrenci güncelleme başarılı.");

}

// delete
void OgrenciIslemleri::on_pushButton_3_clicked()
{

    if(ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()==""){
        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        ui->lineEdit->setText(secili_no);
        ui->lineEdit_2->setText(secili_ad);
        ui->lineEdit_3->setText(secili_soyad);;

        return;
    }

    QSqlQuery query;

    query.prepare("SELECT ogr_no FROM notlar WHERE ogr_no = ?");
    query.bindValue(0, ui->lineEdit->text());
    query.exec();

    int flag=0;
    while (query.next()) {

            if(query.value(0).toString()!=""){
                flag=1;
            }
    }

    if(flag==1){
        QMessageBox messageBox;
        messageBox.information(0,"HATA!","Bu Ogrenci silinemez. Bu Ogrencinin üstüne tanımlanmış dersler vardır!.");
    }

    else{

        query.prepare("DELETE FROM öğrenci WHERE ogr_no = ?");
        query.bindValue(0, ui->lineEdit->text());
        query.exec();


        model = new QSqlQueryModel();
        model->setQuery("SELECT ogr_no, ogr_ad, ogr_soyad FROM öğrenci");
        model->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
        model->setHeaderData(1, Qt::Horizontal, tr("ogr_ad"));
        model->setHeaderData(1, Qt::Horizontal, tr("ogr_soyad"));
        ui->tableView->setModel(model);

        QItemSelectionModel *sm = ui->tableView->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                    this, SLOT(selected(QModelIndex,QModelIndex)));

        QMessageBox messageBox;
        messageBox.information(0,"Başarılı!","Ogrenci silme başarılı.");

    }
}

void OgrenciIslemleri::closeEvent(QCloseEvent *event)
{

    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Onay",
                                                                    tr("Yes: Ana menüye dön\nNo: Uygulamadan ayrıl\n"),
                                                                    QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);

    if(resBtn == QMessageBox::Yes){

        this->close();
        MainWindow *dialog = new MainWindow();
        dialog->show();

    }

}
