#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <QListWidget>
#include <QMessageBox>


extern int oyuncu1;
extern int oyuncu2;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void enable();

    void on_pushButton_2_clicked();
    static void tahmin(int rn, int max, int id, QListWidget * widget);

private:
    Ui::MainWindow *ui;
    int ran=-1;
};
#endif // MAINWINDOW_H
