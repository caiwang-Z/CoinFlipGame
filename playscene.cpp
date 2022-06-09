#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include "mycoin.h"
#include <QPropertyAnimation>
#include <QSound>
//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}


PlayScene::PlayScene(int levelNum, QVector<QVector<int>> v){
    QString str = QString("Welcome to %1th level").arg(levelNum);
    qDebug() << str;

    levelIndex = levelNum;

    setFixedSize(320, 588);

    setWindowIcon(QIcon(":/res/Coin0001.png"));

    setWindowTitle("Coin flip scene");

    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    QMenu* startMenu = new QMenu("Start");
    bar->addMenu(startMenu);

    QAction* quitAction = new QAction("Quit");
    startMenu->addAction(quitAction);

    connect(quitAction, &QAction::triggered, [=](){
        this->hide();
    });

    // add sound resources
    QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav", this);
    QSound* winSound = new QSound(":/res/LevelWinSound.wav", this);

    MyPushButton* backButton = new MyPushButton(":/res/BackButton.png", "BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(this->width() - backButton->width(), this->height() - backButton->height());


    connect(backButton, &MyPushButton::clicked, this, [=](){
        backSound->play();

//       qDebug() << "return to main scene!.";
        QTimer::singleShot(500, this, [=](){
            emit this->chooseSceneBack();

        });


    });

    // show the number of level
    QLabel* label = new QLabel();
    label->setParent(this);

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(15);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50, 120, 50);

    // initialize the gameArray for every level
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            gameArray[i][j] = v[i][j];

        }
    }

    // show the picture by winnning the game
    QLabel* winLabel = new QLabel();
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width())*0.5, -tmpPix.height());

    // show the coin background
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            // show the background of coin
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel* label = new QLabel;
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            // show the coin
            QString str;
            if (gameArray[i][j] == 1){
                str = ":/res/Coin0001.png";
            }
            else{
                str = ":/res/Coin0008.png";
            }


            MyCoin* mycoin = new MyCoin(str);
            mycoin->setParent(this);
            mycoin->move(59 + i * 50, 204 + j * 50);

            // initialize property of coin
            mycoin->posX = i;
            mycoin->posY = j;
            mycoin->flag = gameArray[i][j];

            coinArr[i][j] = mycoin;

            // flip the coin when clicking on the coin
            connect(mycoin, &MyCoin::clicked, this, [=](){
                flipSound->play();

                mycoin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;

                QTimer::singleShot(300, this, [=](){
                    // Flip the coin around
                    // Flip the coin on the right

                    if (mycoin->posX + 1 <= 3){
                        coinArr[mycoin->posX + 1][mycoin->posY]->changeFlag();
                        gameArray[mycoin->posX + 1][mycoin->posY] = gameArray[mycoin->posX + 1][mycoin->posY] == 0 ? 1 : 0;
                    }
                    // Flip the coin on the left
                    if (mycoin->posX - 1 >= 0){
                        coinArr[mycoin->posX - 1][mycoin->posY]->changeFlag();
                        gameArray[mycoin->posX - 1][mycoin->posY] = gameArray[mycoin->posX - 1][mycoin->posY] == 0 ? 1 : 0;
                    }
                    // Flip the coin above
                    if (mycoin->posY + 1 <= 3){
                        coinArr[mycoin->posX][mycoin->posY + 1]->changeFlag();
                        gameArray[mycoin->posX][mycoin->posY + 1] = gameArray[mycoin->posX][mycoin->posY + 1] == 0 ? 1 : 0;
                    }
                    // Flip the coin below
                    if (mycoin->posY - 1 >= 0){
                        coinArr[mycoin->posX][mycoin->posY - 1]->changeFlag();
                        gameArray[mycoin->posX][mycoin->posY - 1] = gameArray[mycoin->posX][mycoin->posY - 1] == 0 ? 1 : 0;
                    }
                    // to determine if game is finished. All gold coins. No sivler coins
                    isWin = true;
                    for (int i = 0; i < 4; i++){
                        for (int j = 0; j < 4; j++){
                            if (coinArr[i][j]->flag == false){
                                isWin = false;
                                break;
                            }
                        }
                    }
                    if (isWin){
                        winSound->play();
                        qDebug() << "You won the game! Congratulations";
                        for (int i = 0; i < 4; i++){
                            for (int j = 0; j < 4; j++){
                                coinArr[i][j]->isWin = true;
                            }
                        }
                        // pull down the winning background
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel, "geometry");
                        // set the duration
                        animation->setDuration(1000);
                        // set the start position
                        animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        // set the end position
                        animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 114, winLabel->width(), winLabel->height()));
                        // set the moving curve or animation effect
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        // execute the animation
                        animation->start();

                    }

                });


            });
        }
    }



}


void PlayScene::paintEvent(QPaintEvent*){
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width() * 0.5 - pix.width() * 0.5, 30, pix.width(), pix.height(), pix);

}
