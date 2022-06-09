#include "mycoin.h"
#include <QDebug>
#include <QTimer>
//MyCoin::MyCoin(QWidget *parent)
//    : QWidget{parent}
//{

//}

MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if (!ret){
        qDebug() << btnImg << "Loading image failed.";
    }
    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border:0px}");
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));

    // initialize the timer object
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString picPath;
        picPath = QString(":/res/Coin000%1").arg(min++);
        bool ret = pix.load(picPath);

        if (!ret){
            qDebug() << picPath << "Loading image failed.";
            return;
        }
        if (min > max){
            min = 1;
            stillInAnimation = false;
            timer1->stop();
        }

        setIcon(pix);

    });

    connect(timer2, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString picPath;
        picPath = QString(":/res/Coin000%1").arg(max--);
        bool ret = pix.load(picPath);

        if (!ret){
            qDebug() << picPath << "Loading image failed.";
            return;
        }
        if (max < min ){
            max = 8;
            stillInAnimation = false;
            timer2->stop();
        }

        setIcon(pix);

    });


}


void MyCoin::mousePressEvent(QMouseEvent* e){
    if (stillInAnimation || isWin){
        return;  // if the animation is not finished, take the mousePressEvent and does not deliver it
    }
    else{
        QPushButton::mousePressEvent(e);  // deliver the mousePressEvent  
    }

}

void MyCoin::changeFlag(){
    // obverse side to reverse side
    if (flag){
        timer1->start(30);
        flag = false;
    }
    else{
        timer2->start(30);
        flag = true;
    }
    stillInAnimation = true;  // the animation begins



}
