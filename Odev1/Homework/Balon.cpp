#include <QRandomGenerator>
#include "clickablelabel.h"

class Balon{

public:

    // Constructor
    Balon(ClickableLabel *label_temp, int wid){

        x= 9 + (QRandomGenerator::global()->generate() % (wid-68));
        label=label_temp;

        label->setFixedWidth(50);
        label->setFixedHeight(50);

        label->move(x,80);

        int a=QRandomGenerator::global()->generate()%7;
        QString temp = ":/images/images/"+QString::number(a)+".jpg";

        QPixmap pix(temp);
        label->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio));

        label->show();
    }

    // balonun konumunu asagiya kaydirma
    void new_move(){

        getLabel()->move(x, getLabel()->pos().y()+6);

    }

    // balon disari ciktimi kontrolu
    static int check(Balon *bal, int H){

        if(bal->label->pos().y()>H+4){
            return 1;
        }

        else{
            return 0;
        }

    }

    ClickableLabel * getLabel(){
        return label;
    }

private:

    // balon konumu
    int x;

    // tiklanabilir label
    ClickableLabel *label;

};
