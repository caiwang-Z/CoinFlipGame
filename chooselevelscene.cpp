#include "chooselevelscene.h"
#include <QMenubar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "playscene.h"
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    dc = new dataConfig();

    setFixedSize(320, 588);

    setWindowIcon(QIcon(":/res/Coin0001.png"));

    setWindowTitle("Select the level scenario");

    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    QMenu* startMenu = new QMenu("Start");
    bar->addMenu(startMenu);

    QAction* quitAction = new QAction("Quit");
    startMenu->addAction(quitAction);

    connect(quitAction, &QAction::triggered, [=](){
        this->hide();
    });

    // sound for the selection of the level
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav", this);

    // sound for the press of the back button
    QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);

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

    for (int i = 0; i < 20; i++){
        MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        connect(menuBtn, &MyPushButton::clicked, this, [=](){
            chooseSound->play();

            QString str = QString("You selected %1 level").arg(i + 1);
            qDebug() << str;

            this->hide();
            playScene = new PlayScene(i + 1, dc->mData[i + 1]);
            playScene->setGeometry(this->geometry());
            playScene->show();

            connect(playScene, &PlayScene::chooseSceneBack, this, [=](){

                this->setGeometry(playScene->geometry());
                this->show();

                delete playScene;
                playScene = nullptr;
            });

        });

        QLabel* label = new QLabel(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}


void ChooseLevelScene::paintEvent(QPaintEvent*){
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width() * 0.5 - pix.width() * 0.5, 30, pix.width(), pix.height(), pix);

}
