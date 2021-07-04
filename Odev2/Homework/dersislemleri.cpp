#include "dersislemleri.h"
#include "ui_dersislemleri.h"
#include <QMessageBox>
#include "mainwindow.h"

DersIslemleri::DersIslemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DersIslemleri)
{

    ui->setupUi(this);

    this->setFixedSize(664, 525);
    ui->lineEdit->setValidator(new QIntValidator(-999999999, 999999999, this) );

    model = new QSqlQueryModel();
    model->setQuery("SELECT ders_kodu, ders_adi FROM dersler");
    model->setHeaderData(0, Qt::Horizontal, tr("ders_kodu"));
    model->setHeaderData(1, Qt::Horizontal, tr("ders_adi"));
    ui->tableView->setModel(model);

    QItemSelectionModel *sm = ui->tableView->selectionModel();
    connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(selected(QModelIndex,QModelIndex)));

    model_ogr = new QSqlQueryModel();
    QString comand = QString("SELECT ogr_no, ders_kodu, vize_not, final_not, geçme_notu FROM notlar WHERE ders_kodu = ")+secili_kod;
    model_ogr->setQuery(comand);
    model_ogr->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model_ogr->setHeaderData(1, Qt::Horizontal, tr("ders_kodu"));
    model_ogr->setHeaderData(2, Qt::Horizontal, tr("vize_not"));
    model_ogr->setHeaderData(3, Qt::Horizontal, tr("final_not"));
    model_ogr->setHeaderData(4, Qt::Horizontal, tr("geçme_notu"));
    ui->tableView_2->setModel(model_ogr);

}

DersIslemleri::~DersIslemleri()
{
    delete ui;
}


void DersIslemleri::selected(QModelIndex a,QModelIndex b){

    QModelIndex index = model->index(a.row(), 0, QModelIndex());
    QModelIndex index1 = model->index(a.row(), 1, QModelIndex());
    secili_kod = qPrintable(ui->tableView->model()->data(index).toString());
    secili_ad = qPrintable(ui->tableView->model()->data(index1).toString());

    model_ogr = new QSqlQueryModel();
    QString comand = QString("SELECT ogr_no, ders_kodu, vize_not, final_not, geçme_notu FROM notlar WHERE ders_kodu = ")+secili_kod;
    model_ogr->setQuery(comand);
    model_ogr->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
    model_ogr->setHeaderData(1, Qt::Horizontal, tr("ders_kodu"));
    model_ogr->setHeaderData(2, Qt::Horizontal, tr("vize_not"));
    model_ogr->setHeaderData(3, Qt::Horizontal, tr("final_not"));
    model_ogr->setHeaderData(4, Qt::Horizontal, tr("geçme_notu"));
    ui->tableView_2->setModel(model_ogr);

    ui->lineEdit->setText(secili_kod);
    ui->lineEdit_2->setText(secili_ad);


}

// Yeni kayit
void DersIslemleri::on_pushButton_clicked()
{

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()==""){
        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO dersler(ders_kodu, ders_adi) "
                              "VALUES (?, ?)");

    query.bindValue(0, ui->lineEdit->text());
    query.bindValue(1, ui->lineEdit_2->text());

    if(query.exec()==1){

        model = new QSqlQueryModel();
        model->setQuery("SELECT ders_kodu, ders_adi FROM dersler");
        model->setHeaderData(0, Qt::Horizontal, tr("ders_kodu"));
        model->setHeaderData(1, Qt::Horizontal, tr("ders_adi"));
        ui->tableView->setModel(model);

        QItemSelectionModel *sm = ui->tableView->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                    this, SLOT(selected(QModelIndex,QModelIndex)));

        QMessageBox messageBox;
        messageBox.information(0,"Başarılı!","Ders ekleme başarılı.");

    }

    else{
        QMessageBox messageBox;
        messageBox.information(0,"HATA!","Bu kodda başka bir ders vardır. Farklı kodda ders ekleyiniz!");

        ui->lineEdit->setText(secili_kod);
        ui->lineEdit_2->setText(secili_ad);
    }

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");

}

// Guncelle
void DersIslemleri::on_pushButton_2_clicked()
{

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()==""){
        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        ui->lineEdit->setText(secili_kod);
        ui->lineEdit_2->setText(secili_ad);

        return;
    }

    QSqlQuery query;

    query.prepare("UPDATE dersler SET ders_kodu = ?, ders_adi = ? WHERE ders_kodu = ?");
    query.bindValue(0, ui->lineEdit->text());
    query.bindValue(1, ui->lineEdit_2->text());
    query.bindValue(2, secili_kod);

    if(query.exec()==1){

        query.prepare("UPDATE notlar SET ders_kodu = ? WHERE ders_kodu = ?");
        query.bindValue(0, ui->lineEdit->text());
        query.bindValue(1, secili_kod);
        query.exec();

        model = new QSqlQueryModel();
        model->setQuery("SELECT ders_kodu, ders_adi FROM dersler");
        model->setHeaderData(0, Qt::Horizontal, tr("ders_kodu"));
        model->setHeaderData(1, Qt::Horizontal, tr("ders_adi"));
        ui->tableView->setModel(model);

        QItemSelectionModel *sm = ui->tableView->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                    this, SLOT(selected(QModelIndex,QModelIndex)));


        model_ogr = new QSqlQueryModel();
        QString comand = QString("SELECT ogr_no, ders_kodu, vize_not, final_not, geçme_notu FROM notlar WHERE ders_kodu = ")+ui->lineEdit->text();
        model_ogr->setQuery(comand);
        model_ogr->setHeaderData(0, Qt::Horizontal, tr("ogr_no"));
        model_ogr->setHeaderData(1, Qt::Horizontal, tr("ders_kodu"));
        model_ogr->setHeaderData(2, Qt::Horizontal, tr("vize_not"));
        model_ogr->setHeaderData(3, Qt::Horizontal, tr("final_not"));
        model_ogr->setHeaderData(4, Qt::Horizontal, tr("geçme_notu"));
        ui->tableView_2->setModel(model_ogr);

        secili_kod = ui->lineEdit->text();
        secili_ad = ui->lineEdit_2->text();

        QMessageBox messageBox;
        messageBox.information(0,"Başarılı!","Ders güncelleme başarılı.");

    }

    else{
        QMessageBox messageBox;
        messageBox.information(0,"Hata!","Bu kodda başka bir ders vardır. Farklı kodda ders güncelleyiniz!");
    }


}

// delete
void DersIslemleri::on_pushButton_3_clicked()
{

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()==""){
        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        ui->lineEdit->setText(secili_kod);
        ui->lineEdit_2->setText(secili_ad);

        return;
    }

    QSqlQuery query;

    query.prepare("SELECT ogr_no FROM notlar WHERE ders_kodu = ?");
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
        messageBox.information(0,"HATA!","Bu ders silinemez. Bu derse kayıtlı öğrenciler var!.");
    }

    else{

        query.prepare("DELETE FROM dersler WHERE ders_kodu = ?");
        query.bindValue(0, ui->lineEdit->text());
        query.exec();

        model = new QSqlQueryModel();
        model->setQuery("SELECT ders_kodu, ders_adi FROM dersler");
        model->setHeaderData(0, Qt::Horizontal, tr("ders_kodu"));
        model->setHeaderData(1, Qt::Horizontal, tr("ders_adi"));
        ui->tableView->setModel(model);

        QItemSelectionModel *sm = ui->tableView->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                    this, SLOT(selected(QModelIndex,QModelIndex)));

        QMessageBox messageBox;
        messageBox.information(0,"BASARILI!","Ders silme islemi basarili!.");
    }

}

void DersIslemleri::closeEvent(QCloseEvent *event)
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
