#include "labyrinthwidget.h"
#include "QMessageBox"
#include "QCoreApplication"
#include "QKeyEvent"

labyrinthWidget::labyrinthWidget(QWidget *parent)
    : QWidget(parent)
{
    _labyrintsLoaded = new bool[3];
    _gridLayout = new QGridLayout();
    setLayout(_gridLayout);
    _backButton = new QPushButton("Vissza");
    _pauseButton = new QPushButton("Stop");
    _easyLabyrinthButton = new QPushButton("Könnyű");
    _mediumLabyrinthButton = new QPushButton("Közepes");
    _hardLabyrinthButton = new QPushButton("Nehéz");
    _timerLabel = new QLabel();
    _timerLabel->setAlignment(Qt::AlignCenter);
    _gridLayout->addWidget(_backButton, 0, 0);
    _gridLayout->addWidget(_pauseButton, 0, 1);
    _gridLayout->addWidget(_easyLabyrinthButton, 0, 0);
    _gridLayout->addWidget(_mediumLabyrinthButton, 1, 0);
    _gridLayout->addWidget(_hardLabyrinthButton, 2, 0);
    _gridLayout->addWidget(_timerLabel, 3, 1);
    _labyrinthLoad = new LabyrinthLoad();
    _labyrinthModel = new labyrinthModel();
    connect(_easyLabyrinthButton, SIGNAL(clicked()), this, SLOT(showEasyLabyrinth()));
    connect(_mediumLabyrinthButton, SIGNAL(clicked()), this, SLOT(showMediumLabyrinth()));
    connect(_hardLabyrinthButton, SIGNAL(clicked()), this, SLOT(showHardLabyrinth()));
    connect(_backButton, SIGNAL(clicked()), this, SLOT(showMenu()));
    connect(_pauseButton, SIGNAL(clicked()), this, SLOT(modelTimeStop()));
    connect(_labyrinthModel->_timer, SIGNAL(timeout()), this, SLOT(updateTimeLabel()));
    _stop = true;
    showMenu();
}

labyrinthWidget::~labyrinthWidget()
{
}

void labyrinthWidget::showMenu()
{
    setWindowTitle("Labirintus");
    setMinimumSize(300, 200);
    resize(300, 200);
    _backButton->setHidden(true);
    _pauseButton->setHidden(true);
    _timerLabel->setHidden(true);
    _easyLabyrinthButton->setHidden(false);
    _mediumLabyrinthButton->setHidden(false);
    _hardLabyrinthButton->setHidden(false);
    _gridLayout->setAlignment(Qt::AlignVCenter);
    _gridLayout->setSpacing(22);
    for (int i = 0; i<3; ++i)
    {
        _labyrintsLoaded[i] = false;
    }
    _pauseButton->setText("Stop");
    modelTimeStop();
    _labyrinthModel->resetFirstMove();
    _labyrinthModel->resetTime();
    _timerLabel->setText("");
    update();
}

void labyrinthWidget::showEasyLabyrinth()
{
    _easyLabyrinthButton->setHidden(true);
    _mediumLabyrinthButton->setHidden(true);
    _hardLabyrinthButton->setHidden(true);
    _backButton->setHidden(false);
    _pauseButton->setHidden(false);
    _timerLabel->setHidden(false);
    _gridLayout->setAlignment(Qt::AlignTop);
    _labyrintsLoaded[0] = !_labyrintsLoaded[0];
    _gridLayout->setSpacing(4);
}

void labyrinthWidget::showMediumLabyrinth()
{
    _easyLabyrinthButton->setHidden(true);
    _mediumLabyrinthButton->setHidden(true);
    _hardLabyrinthButton->setHidden(true);
    _backButton->setHidden(false);
    _pauseButton->setHidden(false);
    _timerLabel->setHidden(false);
    _gridLayout->setAlignment(Qt::AlignTop);
    _labyrintsLoaded[1] = !_labyrintsLoaded[1];
    _gridLayout->setSpacing(4);
}

void labyrinthWidget::showHardLabyrinth()
{
    _easyLabyrinthButton->setHidden(true);
    _mediumLabyrinthButton->setHidden(true);
    _hardLabyrinthButton->setHidden(true);
    _backButton->setHidden(false);
    _pauseButton->setHidden(false);
    _timerLabel->setHidden(false);
    _gridLayout->setAlignment(Qt::AlignTop);
    _labyrintsLoaded[2] = !_labyrintsLoaded[2];
    _gridLayout->setSpacing(4);
}

void labyrinthWidget::modelTimeStop()
{
    if (_pauseButton->text() == "Start")
    {
        _pauseButton->setText("Stop");
        _labyrinthModel->startTime();
        _stop = false;
    }
    else if (_pauseButton->text() == "Stop")
    {
        _pauseButton->setText("Start");
        _labyrinthModel->stopTime();
        _stop = true;
    }
}

void labyrinthWidget::modelCheckFinish()
{
    if (_labyrinthModel->checkFinish())
    {
        modelTimeStop();
        QMessageBox msg;
        msg.setText("Gratulálok kijutottál a labirintusból " + QString::number(_labyrinthModel->_totalTime/1000) + "mp alatt.");
        _labyrinthModel->resetFirstMove();
        _labyrinthModel->resetTime();
        _timerLabel->setText("");
        msg.exec();
        showMenu();
    }
}

void labyrinthWidget::updateTimeLabel()
{
    _timerLabel->setText(QString::number((_labyrinthModel->_totalTime+_labyrinthModel->_time->elapsed())/1000)+" sec");
}

void labyrinthWidget::paintEvent(QPaintEvent* )
{
    QPixmap player(":/pictures/link.jpg");
    QPixmap flag(":/pictures/flag.png");
    QPainter _painter(this);
    if (_labyrintsLoaded[0] && _labyrinthLoad->loadSucces("easy"))
    {
        _labyrinthModel->calculateVisibility("easy");
        setMinimumSize(520, 580);
        _painter.drawRect(10, 70, (width()-20)/_labyrinthLoad->mapSize()*_labyrinthLoad->mapSize(),
                          (height()-80)/_labyrinthLoad->mapSize()*_labyrinthLoad->mapSize());
        _painter.setBrush(Qt::SolidPattern);
        for (int i = 0; i<_labyrinthLoad->mapSize() * _labyrinthLoad->mapSize(); ++i)
        {
            if ((_labyrinthLoad->getMap())[i] == "f" && _labyrinthModel->visiblePlatforms().contains(i))
            {
                _painter.setBrush(Qt::black);
                _painter.drawRect(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                  (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize());
            }
            else if ((_labyrinthLoad->getMap())[i] == "p" && _labyrinthModel->visiblePlatforms().contains(i))
            {
                _painter.setBrush(Qt::white);
                _painter.drawRect(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                  (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize());
            }
            if (i == _labyrinthModel->player())
            {
                _painter.drawPixmap(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                    (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize(), player);
            }
        }
        _painter.drawPixmap((_labyrinthLoad->mapSize()-1)%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                          (_labyrinthLoad->mapSize()-1)/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                            (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize(), flag);
    }
    else if (_labyrintsLoaded[1] && _labyrinthLoad->loadSucces("medium"))
    {
        _labyrinthModel->calculateVisibility("medium");
        setMinimumSize(770, 830);
        _painter.drawRect(10, 70, (width()-20)/_labyrinthLoad->mapSize()*_labyrinthLoad->mapSize(),
                          (height()-80)/_labyrinthLoad->mapSize()*_labyrinthLoad->mapSize());
        _painter.setBrush(Qt::SolidPattern);
        for (int i = 0; i<_labyrinthLoad->mapSize() * _labyrinthLoad->mapSize(); ++i)
        {
            if ((_labyrinthLoad->getMap())[i] == "f" && _labyrinthModel->visiblePlatforms().contains(i))
            {
                _painter.setBrush(Qt::black);
                _painter.drawRect(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                  (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize());
            }
            else if ((_labyrinthLoad->getMap())[i] == "p" && _labyrinthModel->visiblePlatforms().contains(i))
            {
                _painter.setBrush(Qt::white);
                _painter.drawRect(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                  (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize());
            }
            if (i == _labyrinthModel->player())
            {
                _painter.drawPixmap(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                    (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize(), player);
            }
        }
        _painter.drawPixmap((_labyrinthLoad->mapSize()-1)%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                          (_labyrinthLoad->mapSize()-1)/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                            (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize(), flag);
    }
    else if (_labyrintsLoaded[2] && _labyrinthLoad->loadSucces("hard"))
    {
        _labyrinthModel->calculateVisibility("hard");
        setMinimumSize(1020, 1080);
        _painter.drawRect(10, 70, (width()-20)/_labyrinthLoad->mapSize()*_labyrinthLoad->mapSize(),
                          (height()-80)/_labyrinthLoad->mapSize()*_labyrinthLoad->mapSize());
        _painter.setBrush(Qt::SolidPattern);
        for (int i = 0; i<_labyrinthLoad->mapSize() * _labyrinthLoad->mapSize(); ++i)
        {
            if ((_labyrinthLoad->getMap())[i] == "f" && _labyrinthModel->visiblePlatforms().contains(i))
            {
                _painter.setBrush(Qt::black);
                _painter.drawRect(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                  (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize());
            }
            else if ((_labyrinthLoad->getMap())[i] == "p" && _labyrinthModel->visiblePlatforms().contains(i))
            {
                _painter.setBrush(Qt::white);
                _painter.drawRect(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                  (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize());
            }
            if (i == _labyrinthModel->player())
            {
                _painter.drawPixmap(i%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                                  i/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                                    (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize(), player);
            }
        }
        _painter.drawPixmap((_labyrinthLoad->mapSize()-1)%_labyrinthLoad->mapSize()*((width()-20)/_labyrinthLoad->mapSize())+10,
                          (_labyrinthLoad->mapSize()-1)/_labyrinthLoad->mapSize()*((height() - 80)/_labyrinthLoad->mapSize())+70,
                            (width()-20)/_labyrinthLoad->mapSize(), (height()-80)/_labyrinthLoad->mapSize(), flag);
    }
    modelCheckFinish();
}

void labyrinthWidget::keyPressEvent(QKeyEvent *event)
{
    if ((_labyrintsLoaded[0] || _labyrintsLoaded[1] || _labyrintsLoaded[2]) && !_stop)
    {
        if (event->key() == Qt::Key_W)
        {
            _labyrinthModel->moveUp();
            update();
        }
        if (event->key() == Qt::Key_S)
        {
            _labyrinthModel->moveDown();
            update();
        }
        if (event->key() == Qt::Key_A)
        {
            _labyrinthModel->moveLeft();
            update();
        }
        if (event->key() == Qt::Key_D)
        {
            _labyrinthModel->moveRight();
            update();
        }
    }
}

