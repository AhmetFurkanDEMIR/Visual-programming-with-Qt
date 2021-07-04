#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QRandomGenerator>

// Constructor  function
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // monitore gore oyun ekrani duzenlenir
    displaySettings();

    // zaman labeli guncelleme
    time = 1;
    timer_time = new QTimer(this);
    connect(timer_time, SIGNAL(timeout()), this, SLOT(time_update()));
    timer_time->start(1000);

    // otomatik balon cikartma
    timer_BalonSpawn = new QTimer(this);
    connect(timer_BalonSpawn, SIGNAL(timeout()), this, SLOT(spawn()));
    timer_BalonSpawn->start(700);

    // balonlari asagi kaydirma signal&slot
    // balonlarin ekrandan cikma kontrolu
    timer_label = new QTimer(this);
    connect(timer_label, SIGNAL(timeout()), SLOT(move_update()));
    timer_label->start(40);

    // durumu ekranda yazdirmak icin kullanilan labeller.
    vurulan=0;
    kacan=0;

    // oyun ekran ayari
    flagWindow=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

// tum ekranlar ile uyumlu olmasini sagliyorum (1920x1080, 1366x768, vb..)
void MainWindow::displaySettings(){

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height_res = screenGeometry.height();
    int width_res = screenGeometry.width();
    heightH=height_res;
    widthW=width_res;

    this->resize(width_res, height_res);

    ui->label_4->resize(width_res+2, height_res+2);

    QPixmap pix(":/images/images/arkaplan.jpg");
    ui->label_4->setPixmap(pix.scaled(width_res+2,width_res+2,Qt::KeepAspectRatio));

    ui->pushButton->move(width_res-40, 10);
    ui->pushButton_2->move(width_res-76, 10);

    ui->horizontalLayoutMain->setStretch(0,width_res*0.009);

}

// balonlari asagiya kaydirir ayni zamanda kacan balonlari kontrol eder.
void MainWindow::move_update(){

    int count = -1;

    foreach(Balon *bal, balon_list){

        count++;

        // konum guncelleme
        bal->new_move();

        // balon kacti
        if(bal->check(bal, heightH)){

            kacan+=1;
            QString format("Kaçan Balon Sayısı : <font color='red'>%1</font>");
            ui->label_3->setText(format.arg(QString::number(kacan)));

            balon_list.at(count)->getLabel()->hide();
            delete balon_list.at(count);
            balon_list.removeAt(count);
        }
    }

}

// balonu belirlenen sure sonunda tamamen ortadan kaldirir (patlama efektinden sonra).
void MainWindow::balon_hide(){

    if(QueBalon_list.count()!=0){

        QueBalon_list.at(0)->getLabel()->hide();
        delete QueBalon_list.at(0);
        QueBalon_list.removeAt(0);
    }


}

// balona tıklanma eventi
void MainWindow::click_balon(){

    QObject *balon_label = QObject::sender();

    int count = -1;
    foreach(Balon *temp, balon_list){

        count+=1;

        // vurulan balonu&labeli bulduk
        if(balon_label==temp->getLabel()){

            // label update
            vurulan+=1;
            QString format("Vurulan Balon Sayısı : <font color='green'>%1</font>");
            ui->label_2->setText(format.arg(QString::number(vurulan)));

            // patlama efekti
            QPixmap pix(":/images/images/patlama.jpg");
            balon_list.at(count)->getLabel()->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio));

            // patlama efekti bittikten sonra silinmesi için temp bir liste
            QueBalon_list.append(balon_list.at(count));

            // ana yapidan cikartilir
            balon_list.removeAt(count);

            // patlama efekti timeri
            QTimer::singleShot(2500, this, SLOT(balon_hide()));

        }
    }

}

// balonları random spawn
void MainWindow::spawn(){

    ClickableLabel *label = new ClickableLabel(this);
    connect(label, SIGNAL(clicked()), this, SLOT(click_balon()));

    Balon *bal = new Balon(label, widthW);
    balon_list.append(bal);

}

// sure labelini guncelleme fonksiyonu
void MainWindow::time_update(){

    QString format("Süre : <font color='blue'>%1</font>");
    ui->label->setText(format.arg(QString::number(time)));

    time+=1;

}

// ESC tusuna basilir ise oyundan cikilir
// (ALT+Tab ile otomatik asagiya alir). veya sag ustteki tuslari kullanabilirsiniz.
void MainWindow::keyReleaseEvent(QKeyEvent *event){

    if(event->key()==Qt::Key_Escape){
        exit(0);
    }

}

// pencere secilince oyun ekranini tekrardan buyultmek icin fonksiyon.
// oyunun durmasini ve baslamsini saglar, boylece arka planda kendi kendine oynamaz ve kullanici balonlari kacirmaz
void MainWindow::changeEvent(QEvent * event){


    if(flagWindow!=3){
        flagWindow+=1;
    }


    if(this->isMinimized() || (flagWindow==3 && !(this->isActiveWindow()))){
        timer_time->stop();
        timer_label->stop();
        timer_BalonSpawn->stop();
    }

    else if(this->isFullScreen() && flagWindow==3){

        this->showFullScreen();
        timer_time->start();
        timer_label->start();
        timer_BalonSpawn->start();
    }

}


// oyunu (pencereyi kapatmak)
void MainWindow::on_pushButton_clicked()
{
    exit(0);
}

// ekrani kucultmek
void MainWindow::on_pushButton_2_clicked()
{

    timer_time->stop();
    timer_label->stop();
    timer_BalonSpawn->stop();
    this->showMinimized();
}
