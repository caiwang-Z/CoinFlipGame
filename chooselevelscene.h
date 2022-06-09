#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include "playscene.h"
#include "dataconfig.h"


class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);

    PlayScene* playScene = nullptr;

    dataConfig* dc = nullptr;

signals:
    // custom signal needs to be declared, no need to implemented.
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
