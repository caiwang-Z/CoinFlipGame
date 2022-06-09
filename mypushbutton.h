#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
    explicit MyPushButton(QString normalImg, QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;

    // bounce downward
    void zoom1();

    // bounce upward
    void zoom2();

signals:

};

#endif // MYPUSHBUTTON_H
