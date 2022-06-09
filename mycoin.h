#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);

    // property of the coin
    int posX;
    int posY;
    bool flag; // 1 obverse side of the coin; 0 reverse side of the coin
    bool isWin = false;  // if true, means won the game, the coin can not be pressed.
    // function to change the flag
    void changeFlag();
    QTimer* timer1;
    QTimer* timer2;

    int min = 1;

    int max = 8;

    bool stillInAnimation = false;  // to inspect if the animation of coin flip already done or not yet.

    // override the pressEvent
    void mousePressEvent(QMouseEvent* e);


signals:

};

#endif // MYCOIN_H
