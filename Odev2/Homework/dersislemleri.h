#ifndef DERSISLEMLERI_H
#define DERSISLEMLERI_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class DersIslemleri;
}

class DersIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit DersIslemleri(QWidget *parent = nullptr);
    ~DersIslemleri();

private slots:
    void selected(QModelIndex,QModelIndex);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::DersIslemleri *ui;
    QSqlQueryModel *model;
    QSqlQueryModel *model_ogr;

    QString secili_kod;
    QString secili_ad;
};

#endif // DERSISLEMLERI_H
