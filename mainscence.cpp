#include "mainscence.h"
#include "ui_mainscence.h"
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

MainScence::MainScence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScence)
{
    ui->setupUi(this);

    // set fix size of main window
    setFixedSize(320, 588);

    // set application icon
    setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // set title of main window
    setWindowTitle("Coin flip game");

    connect(ui->actionQuit, &QAction::triggered, [=](){
        this->close();

    });

    // background sound behind start button
    QSound* startSound = new QSound(":/res/TapButtonSound.wav", this);

    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    cls = new ChooseLevelScene();

    connect(cls, &ChooseLevelScene::chooseSceneBack, this, [=](){
        startSound->play();

        cls->hide();
        QTimer::singleShot(500, [=](){
            this->setGeometry(cls->geometry());
            this->show();

        });
    });

    connect(startBtn, &MyPushButton::clicked, this, [=](){
        startBtn->zoom1();
        startBtn->zoom2();

        QTimer::singleShot(500, this, [=](){
            this->hide();
            cls->setGeometry(this->geometry());
            cls->show();
        });

    });
}

void MainScence::paintEvent(QPaintEvent*){
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}


MainScence::~MainScence()
{
    delete ui;
}

