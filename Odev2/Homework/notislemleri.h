#ifndef NOTISLEMLERI_H
#define NOTISLEMLERI_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class NotIslemleri;
}

class NotIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit NotIslemleri(QWidget *parent = nullptr);
    ~NotIslemleri();

private slots:
    void on_pushButton_clicked();
    void selected_ogr(QModelIndex a,QModelIndex b);
    void selected_ders(QModelIndex a,QModelIndex b);
    void closeEvent(QCloseEvent *event);

private:
    Ui::NotIslemleri *ui;
    QSqlQueryModel *model_ogr;
    QSqlQueryModel *model_ders;
    QSqlQueryModel *model_tum_ogr;

    QString secili_no;
    QString secili_kod;
};

#endif // NOTISLEMLERI_H
