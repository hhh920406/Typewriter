#include "tankform.h"
#include "ui_tankform.h"

TankForm::TankForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TankForm)
{
    ui->setupUi(this);
    this->gameInitial();
    this->setMouseTracking(true);
}

TankForm::~TankForm()
{
    delete timer;
    delete ui;
    delete mainMenu;
    delete help;
    delete achieve;
    delete game;
    delete over;
    delete stage;
    delete pause;
    delete config;
}

void TankForm::gameInitial()
{
    currentScene = Defination::SCENE_OPENING;
    time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    timer->start(30);
    loading = new Loading();
    mainMenu = new MainMenu();
    help = new Help();
    achieve = new Achieve();
    game = new Game();
    game->bindAchieve(this->achieve);
    over = new Over();
    stage = new Stage();
    pause = new Pause();
    config = new Config();
    config->readInfo();
    game->bindConfig(this->config);
}

void TankForm::timerEvent()
{
    this->update();
}

void TankForm::keyPressEvent(QKeyEvent *event)
{
    switch(this->currentScene)
    {
    case Defination::SCENE_GAME:
        this->game->keyDown(event);
        break;
    case Defination::SCENE_SNAKE:
        this->snake->keyDownEvent(event);
        break;
    }
}

void TankForm::keyReleaseEvent(QKeyEvent *event)
{
    switch(this->currentScene)
    {
    case Defination::SCENE_GAME:
        this->currentScene = this->game->keyRelease(event);
        if(this->currentScene == Defination::SCENE_PAUSE)
        {
            this->pause->lastScene = Defination::SCENE_GAME;
        }
        break;
    case Defination::SCENE_PAUSE:
        this->currentScene = this->pause->lastScene;
        break;
    case Defination::SCENE_CONFIG:
        this->config->keyDown(event);
        break;
    case Defination::SCENE_ABOUT:
        this->currentScene = this->about->keyReleaseEvent(event);
        if(this->currentScene != Defination::SCENE_ABOUT)
        {
            delete this->about;
        }
        break;
    case Defination::SCENE_SNAKE:
        this->currentScene = this->snake->keyReleaseEvent(event);
        if(this->currentScene == Defination::SCENE_PAUSE)
        {
            this->pause->lastScene = Defination::SCENE_SNAKE;
        }
        break;
    case Defination::SCENE_CELLINTRO:
        this->currentScene = this->cellIntro->keyReleaseEvent(event);
        if(this->currentScene != Defination::SCENE_CELLINTRO)
        {
            delete this->cellIntro;
        }
        if(this->currentScene == Defination::SCENE_CELL)
        {
            this->cellScene = new CellScene();
        }
        break;
    case Defination::SCENE_CELL:
        this->currentScene = this->cellScene->keyReleaseEvent(event);
        if(this->currentScene != Defination::SCENE_CELL)
        {
            delete this->cellScene;
        }
    }
}

void TankForm::mousePressEvent(QMouseEvent *event)
{
    switch(this->currentScene)
    {
    case Defination::SCENE_CELL:
        this->cellScene->mouseDownEvent(event);
        break;
    }
}

void TankForm::mouseReleaseEvent(QMouseEvent *event)
{
    switch(this->currentScene)
    {
    case Defination::SCENE_MAIN:
        if(event->button() == Qt::LeftButton)
        {
            this->currentScene = mainMenu->click(event->x(), event->y());
            if(this->currentScene == Defination::SCENE_CHOICE)
            {
                this->choice = new Choice();
            }
            this->mainMenu->moveToPosition();
        }
        break;
    case Defination::SCENE_CHOICE:
        this->currentScene = choice->mouseReleaseEvent(event);
        switch (this->currentScene)
        {
        case Defination::SCENE_STAGE:
            delete this->game;
            this->game = new Game();
            this->game->bindAchieve(this->achieve);
            this->game->bindConfig(this->config);
            this->time = 60;
            break;
        case Defination::SCENE_ABOUT:
            this->about = new AboutUs();
            break;
        case Defination::SCENE_SNAKE:
            this->snake = new SnakeScene();
            this->snake->bindConfig(this->config);
            break;
        case Defination::SCENE_CELLINTRO:
            this->cellIntro = new CellIntro();
            break;
        }
        if(this->currentScene != Defination::SCENE_CHOICE)
        {
            delete this->choice;
        }
        break;
    case Defination::SCENE_ACHIEVE:
    case Defination::SCENE_HELP:
        this->currentScene = Defination::SCENE_MAIN;
        break;
    case Defination::SCENE_PAUSE:
        this->currentScene = this->pause->lastScene;
        break;
    case Defination::SCENE_CONFIG:
        this->currentScene = this->config->mouseDown(event);
        break;
    case Defination::SCENE_OPENING:
        this->currentScene = Defination::SCENE_MAIN;
        delete this->loading;
        break;
    case Defination::SCENE_ABOUT:
        this->currentScene = this->about->mouseReleaseEvent();
        if(this->currentScene != Defination::SCENE_ABOUT)
        {
            delete this->about;
        }
        break;
    case Defination::SCENE_CELLINTRO:
        this->currentScene = this->cellIntro->mouseReleaseEvent();
        if(this->currentScene != Defination::SCENE_CELLINTRO)
        {
            delete this->cellIntro;
        }
        if(this->currentScene == Defination::SCENE_CELL)
        {
            this->cellScene = new CellScene();
        }
        break;
    case Defination::SCENE_CELL:
        this->cellScene->mouseReleaseEvent(event);
    }
}

void TankForm::mouseMoveEvent(QMouseEvent *event)
{
    switch(this->currentScene)
    {
    case Defination::SCENE_MAIN:
        mainMenu->setMousePosition(event->x(), event->y());
        break;
    case Defination::SCENE_CONFIG:
        this->config->mouseMove(event);
        break;
    case Defination::SCENE_CHOICE:
        this->choice->mouseMoveEvent(event);
        break;
    case Defination::SCENE_CELL:
        this->cellScene->mouseMoveEvnet(event);
        break;
    }
}

void TankForm::paintEvent(QPaintEvent *event)
{
    qint32 temp;
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    switch(this->currentScene)
    {
    case Defination::SCENE_OPENING:
        if(loading->draw(time, &painter))
        {
            this->currentScene = Defination::SCENE_MAIN;
            delete loading;
        }
        break;
    case Defination::SCENE_MAIN:
        mainMenu->draw(&painter);
        break;
    case Defination::SCENE_HELP:
        help->draw(&painter);
        break;
    case Defination::SCENE_ACHIEVE:
        achieve->draw(&painter);
        break;
    case Defination::SCENE_STAGE:
        if(stage->draw(&painter, game->currentStage, time))
        {
            this->game->initialStage(this->game->currentStage);
            this->currentScene = Defination::SCENE_GAME;
        }
        break;
    case Defination::SCENE_OVER:
        if(over->draw(&painter, time))
        {
            this->currentScene = Defination::SCENE_MAIN;
            delete this->mainMenu;
            mainMenu = new MainMenu;
        }
        break;
    case Defination::SCENE_GAME:
        temp = game->draw(&painter, time);
        if(temp == Defination::SCENE_STAGE)
        {
            this->game->currentStage ++;
            this->currentScene = Defination::SCENE_STAGE;
            this->time = 60;
            this->achieve->writeData();
        }
        else if(temp == Defination::SCENE_OVER)
        {
            this->currentScene = Defination::SCENE_OVER;
            this->time = 120;
            this->achieve->writeData();
        }
        break;
    case Defination::SCENE_PAUSE:
        this->pause->draw(&painter);
        break;
    case Defination::SCENE_CLOSE:
        this->close();
        break;
    case Defination::SCENE_CONFIG:
        this->config->draw(&painter);
        break;
    case Defination::SCENE_CHOICE:
        this->choice->draw(&painter);
        break;
    case Defination::SCENE_ABOUT:
        this->about->draw(&painter);
        break;
    case Defination::SCENE_SNAKE:
        this->currentScene = this->snake->draw(&painter);
        if(this->currentScene != Defination::SCENE_SNAKE)
        {
            delete this->snake;
            this->time = 60;
        }
        break;
    case Defination::SCENE_CELLINTRO:
        this->cellIntro->draw(&painter);
        break;
    case Defination::SCENE_CELL:
        this->cellScene->draw(&painter);
    }
}
