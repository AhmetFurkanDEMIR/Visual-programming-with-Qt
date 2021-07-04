#ifndef OGRENCIISLEMLERI_H
#define OGRENCIISLEMLERI_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class OgrenciIslemleri;
}

class OgrenciIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit OgrenciIslemleri(QWidget *parent = nullptr);
    ~OgrenciIslemleri();

private slots:
    void on_pushButton_clicked();
    void selected(QModelIndex a,QModelIndex b);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::OgrenciIslemleri *ui;
    QSqlQueryModel *model;

    QString secili_ad;
    QString secili_soyad;
    QString secili_no;
};

#endif // OGRENCIISLEMLERI_H
