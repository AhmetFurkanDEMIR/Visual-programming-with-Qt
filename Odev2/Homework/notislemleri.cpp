#include "notislemleri.h"
#include "ui_notislemleri.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow.h"

NotIslemleri::NotIslemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotIslemleri)
{
    ui->setupUi(this);

    this->setFixedSize(664, 667);
    ui->lineEdit_3->setValidator(new QIntValidator(-999999999, 999999999, this) );
    ui->lineEdit_4->setValidator(new QIntValidator(-999999999, 999999999, this) );

    model_ogr = new QSqlQueryModel();
    model_ogr->setQuery("SELECT ogr_no, ogr_ad, ogr_soyad FROM öğrenci");
    model_ogr->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model_ogr->setHeaderData(1, Qt::Horizontal, tr("ogr_ad"));
    model_ogr->setHeaderData(1, Qt::Horizontal, tr("ogr_soyad"));
    ui->tableView->setModel(model_ogr);

    QItemSelectionModel *sm_ogr = ui->tableView->selectionModel();
    connect(sm_ogr, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(selected_ogr(QModelIndex,QModelIndex)));

    model_ders = new QSqlQueryModel();
    model_ders->setQuery("SELECT ders_kodu, ders_adi FROM dersler");
    model_ders->setHeaderData(0, Qt::Horizontal, tr("ders_kodu"));
    model_ders->setHeaderData(1, Qt::Horizontal, tr("ders_adi"));
    ui->tableView_2->setModel(model_ders);

    QItemSelectionModel *sm_ders = ui->tableView_2->selectionModel();
    connect(sm_ders, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(selected_ders(QModelIndex,QModelIndex)));

    model_tum_ogr = new QSqlQueryModel();
    model_tum_ogr->setQuery("SELECT ogr_no, ders_kodu, vize_not, final_not, geçme_notu FROM notlar");
    model_tum_ogr->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model_tum_ogr->setHeaderData(1, Qt::Horizontal, tr("ders_kodu"));
    model_tum_ogr->setHeaderData(2, Qt::Horizontal, tr("vize_not"));
    model_tum_ogr->setHeaderData(3, Qt::Horizontal, tr("final_not"));
    model_tum_ogr->setHeaderData(4, Qt::Horizontal, tr("geçme_notu"));
    ui->tableView_3->setModel(model_tum_ogr);
}

NotIslemleri::~NotIslemleri()
{
    delete ui;
}

// ders kayit ekle
void NotIslemleri::on_pushButton_clicked()
{

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()=="" || ui->lineEdit_4->text()==""){
        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO notlar(ogr_no, ders_kodu, vize_not, final_not, geçme_notu) "
                              "VALUES (?, ?, ?, ?, ?)");

    query.bindValue(0, ui->lineEdit->text());
    query.bindValue(1, ui->lineEdit_2->text());
    query.bindValue(2, ui->lineEdit_3->text());
    query.bindValue(3, ui->lineEdit_4->text());
    int gecme = ui->lineEdit_3->text().toInt()*0.40 + ui->lineEdit_4->text().toInt()*0.60;
    query.bindValue(4, gecme);
    query.exec();

    model_tum_ogr = new QSqlQueryModel();
    model_tum_ogr->setQuery("SELECT ogr_no, ders_kodu, vize_not, final_not, geçme_notu FROM notlar");
    model_tum_ogr->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model_tum_ogr->setHeaderData(1, Qt::Horizontal, tr("ders_kodu"));
    model_tum_ogr->setHeaderData(2, Qt::Horizontal, tr("vize_not"));
    model_tum_ogr->setHeaderData(3, Qt::Horizontal, tr("final_not"));
    model_tum_ogr->setHeaderData(4, Qt::Horizontal, tr("geçme_notu"));
    ui->tableView_3->setModel(model_tum_ogr);

    QMessageBox messageBox;
    messageBox.information(0,"Başarılı!","Ders Kayit Ekleme başarılı.");

}

void NotIslemleri::selected_ogr(QModelIndex a,QModelIndex b){

    QModelIndex index = model_ogr->index(a.row(), 0, QModelIndex());
    secili_no = qPrintable(ui->tableView->model()->data(index).toString());


    ui->lineEdit->setText(secili_no);

}

void NotIslemleri::selected_ders(QModelIndex a,QModelIndex b){

    QModelIndex index = model_ders->index(a.row(), 0, QModelIndex());
    secili_kod = qPrintable(ui->tableView_2->model()->data(index).toString());

    ui->lineEdit_2->setText(secili_kod);

}

void NotIslemleri::closeEvent(QCloseEvent *event)
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
