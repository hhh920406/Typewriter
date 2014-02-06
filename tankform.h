#ifndef TANKFORM_H
#define TANKFORM_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QMessageBox>

#include "defination.h"
#include "loading.h"
#include "mainmenu.h"
#include "help.h"
#include "achieve.h"
#include "game.h"
#include "over.h"
#include "stage.h"
#include "pause.h"
#include "config.h"
#include "choice.h"
#include "aboutus.h"
#include "snakescene.h"
#include "cellintro.h"
#include "cellscene.h"

namespace Ui {
    class TankForm;
}

class TankForm : public QWidget
{
    Q_OBJECT

public:
    explicit TankForm(QWidget *parent = 0);
    ~TankForm();

private:
    Ui::TankForm *ui;
    qint32 currentScene;
    qint32 time;
    QTimer *timer;
    Loading *loading;
    MainMenu *mainMenu;
    Help *help;
    Achieve *achieve;
    Game *game;
    Over *over;
    Stage *stage;
    Pause *pause;
    Config *config;
    Choice *choice;
    AboutUs *about;
    SnakeScene *snake;
    CellIntro *cellIntro;
    CellScene *cellScene;

    void gameInitial();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void timerEvent();
};

#endif
