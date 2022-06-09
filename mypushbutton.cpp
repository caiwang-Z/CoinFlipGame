#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>


//MyPushButton::MyPushButton(QWidget *parent)
//    : QPushButton{parent}
//{

//}


MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    normalImgPath = normalImg;
    pressImgPath = pressImg;

    QPixmap pix;

    bool ret = pix.load(normalImgPath);
    if (!ret){
        qDebug() << "Loading picture: " << normalImgPath << " failed. \n";
        return;
    }

    // set fixed size of button
    setFixedSize(pix.width(), pix.height());

    // set style sheet of the button
    setStyleSheet("QPushButton{border:0px}");

    // set icon of the button
    setIcon(pix);

    // set icon size of the button
    setIconSize(QSize(pix.width(), pix.height()));

}


void MyPushButton::zoom1(){
    QPropertyAnimation* ani = new QPropertyAnimation(this, "geometry");
    ani->setDuration(200);

    // start value
    ani->setStartValue(QRect(x(), y(), width(), height()));

    // set end value
    ani->setEndValue(QRect(x(), y() + 10, width(), height()));

    ani->setEasingCurve(QEasingCurve::OutBounce);

    ani->start();
}

void MyPushButton::zoom2(){
    QPropertyAnimation* ani = new QPropertyAnimation(this, "geometry");
    ani->setDuration(200);

    // start value
    ani->setStartValue(QRect(x(), y() + 10, width(), height()));

    // set end value
    ani->setEndValue(QRect(x(), y(), width(), height()));

    ani->setEasingCurve(QEasingCurve::OutBounce);

    ani->start();
}
