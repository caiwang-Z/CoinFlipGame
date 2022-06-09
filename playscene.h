#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include "dataconfig.h"
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum, QVector<QVector<int>> v);

    void paintEvent(QPaintEvent*);

    int levelIndex;

    bool isWin;  // to determine if the game has been won

    int gameArray[4][4];  // maintain an array to distinct the gold coin and silver coin

    MyCoin* coinArr[4][4];  // maintain all coins in the playscene
signals:
   void chooseSceneBack();


};

#endif // PLAYSCENE_H
