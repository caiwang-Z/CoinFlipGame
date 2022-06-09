#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>
#include <QAction>
#include <QPaintEvent>
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScence; }
QT_END_NAMESPACE

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    MainScence(QWidget *parent = nullptr);
    ~MainScence();

    void paintEvent(QPaintEvent*);

private:
    Ui::MainScence *ui;
    ChooseLevelScene* cls;
};
#endif // MAINSCENCE_H
