#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include "Balon.cpp"
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern int heightH;
extern int widthW;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // ESC tusuna basinca oyundan cikmasini saglamak icin tetikleme
    void keyReleaseEvent(QKeyEvent *);

    // minimize halden tekrardan büyültülme olur ise oyunu full ekran yapma signali.
    void changeEvent(QEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    // sure labelini guncelleyen fonksiyon
    void time_update();

    // balonların otomatik spawn olmasi
    void spawn();

    // balonlari asagiya kaydirir.
    void move_update();

    // balona tıklanma eventi
    void click_balon();

    // balonu belirlenen sure sonunda tamamen ortadan kaldirir
    void balon_hide();

    // tum ekranlar ile uyumlu olmasini sagliyorum
    void displaySettings();

private:
    Ui::MainWindow *ui;
    int time, vurulan, kacan, flagWindow;

    QList<Balon *> balon_list;
    QList<Balon *> QueBalon_list;

    QTimer *timer_time;
    QTimer *timer_BalonSpawn;
    QTimer *timer_label;
};
#endif // MAINWINDOW_H
