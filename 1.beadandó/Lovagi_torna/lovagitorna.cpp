#include "lovagitorna.h"

lovagiTorna::lovagiTorna(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(600, 600);
    setBaseSize(600,600);
    setWindowTitle(tr("Lovagi torna"));

    _newGameButton = new QPushButton(tr("Új játék")); // új játék gomb
    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));

    _mainLayout = new QVBoxLayout(); // függőleges rendező a teljes felületnek
    _mainLayout->addWidget(_newGameButton);

    _tableLayout = new QGridLayout(); // rácsos rendező a játékmezőnek
    generateField();

    _mainLayout->addLayout(_tableLayout);
    setLayout(_mainLayout);

    newGame();
}

lovagiTorna::~lovagiTorna()
{
}

void lovagiTorna::generateField()
{
    _gameTable = new int*[8];
    _buttonTable.resize(8);

    for (int i = 0; i < 8; ++i)
    {
        _gameTable[i] = new int[8];
        _buttonTable[i].resize(8);
        for (int j = 0; j < 8; ++j)
        {
            _buttonTable[i][j]= new QPushButton(this);
            _buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            _tableLayout->addWidget(_buttonTable[i][j], i, j); // gombok felvétele a rendezőbe

            connect(_buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
}

void lovagiTorna::newGame()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            _gameTable[i][j] = 0;
            _buttonTable[i][j]->setText("");
            _buttonTable[i][j]->setStyleSheet("background-color: silver;");
            _buttonTable[i][j]->setEnabled(false);
        }
    }
    _buttonTable[0][0]->setEnabled(true);
    _buttonTable[7][7]->setEnabled(true);
    _buttonTable[0][0]->setStyleSheet("image: url(:/black_horse.png); background-color: silver;");
    _buttonTable[7][7]->setStyleSheet("image: url(:/black_horse.png); background-color: silver;");
    _buttonTable[7][0]->setStyleSheet("image: url(:/white_horse.png); background-color: silver;");
    _buttonTable[0][7]->setStyleSheet("image: url(:/white_horse.png); background-color: silver;");
    _currentPlayer = 1;
    _horses = new int*[2];
    _horses[0] = new int[4];
    _horses[1] = new int[4];
    _horses[0][0] = 0;
    _horses[0][1] = 0;
    _horses[0][2] = 7;
    _horses[0][3] = 7;
    _horses[1][0] = 7;
    _horses[1][1] = 0;
    _horses[1][2] = 0;
    _horses[1][3] = 7;
    _firstMove = new bool*[2];
    _firstMove[0] = new bool[2];
    _firstMove[1] = new bool[2];
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            _firstMove[i][j] = true;
        }
    }
}

void lovagiTorna::stepGame(int x, int y)
{
    _gameTable[x][y] = _currentPlayer;

    if (_currentPlayer == 1)
    {
        _buttonTable[x][y]->setStyleSheet("image: url(:/black_horse.png); background-color: rgb(75, 75, 75);");
        if (_selected / 8 == 0 && _selected % 8 == 0 && _firstMove[0][0])
        {
            _buttonTable[_selected / 8][_selected % 8]->setStyleSheet("background-color: silver;");
            _firstMove[0][0] = false;
        }
        else if (_selected / 8 == 7 && _selected % 8 == 7 && _firstMove[0][1])
        {
            _buttonTable[_selected / 8][_selected % 8]->setStyleSheet("background-color: silver;");
            _firstMove[0][1] = false;
        }
        else
            _buttonTable[_selected / 8][_selected % 8]->setStyleSheet("background-color: rgb(75, 75, 75);");
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                _buttonTable[i][j]->setEnabled(false);
            }
        }
        _buttonTable[ _horses[1][0] ][ _horses[1][1] ]->setEnabled(true);
        _buttonTable[ _horses[1][2] ][ _horses[1][3] ]->setEnabled(true);
    }
    else
    {
        _buttonTable[x][y]->setStyleSheet("image: url(:/white_horse.png); background-color: white;");
        if (_selected / 8 == 7 && _selected % 8 == 0 && _firstMove[1][0])
        {
            _buttonTable[_selected / 8][_selected % 8]->setStyleSheet("background-color: silver;");
            _firstMove[1][0] = false;
        }
        else if (_selected / 8 == 0 && _selected % 8 == 7 && _firstMove[1][1])
        {
            _buttonTable[_selected / 8][_selected % 8]->setStyleSheet("background-color: silver;");
            _firstMove[1][1] = false;
        }
        else
            _buttonTable[_selected / 8][_selected % 8]->setStyleSheet("background-color: white;");
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                _buttonTable[i][j]->setEnabled(false);
            }
        }
        _buttonTable[ _horses[0][0] ][ _horses[0][1] ]->setEnabled(true);
        _buttonTable[ _horses[0][2] ][ _horses[0][3] ]->setEnabled(true);

    }
    _currentPlayer = _currentPlayer % 2 + 1;
    checkGame();
}

void lovagiTorna::checkGame()
{
    int won = 0;

    for(int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
             if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i][j+1] && _gameTable[i][j] == _gameTable[i][j+2]
                 && _gameTable[i][j] == _gameTable[i][j+3])
                 won = _gameTable[i][j];
        }
    }
    for(int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
             if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i+1][j] && _gameTable[i][j] == _gameTable[i+2][j]
                 && _gameTable[i][j] == _gameTable[i+3][j])
                 won = _gameTable[i][j];
        }
    }
    for(int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 8 - i; ++j)
        {
             if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i+1][j+1] && _gameTable[i][j] == _gameTable[i+2][j+2]
                 && _gameTable[i][j] == _gameTable[i+3][j+3])
                 won = _gameTable[i][j];
        }
    }
    for(int i = 0; i < 5; ++i)
    {
        for (int j = 3; j < 8; ++j)
        {
             if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i+1][j-1] && _gameTable[i][j] == _gameTable[i+2][j-2]
                 && _gameTable[i][j] == _gameTable[i+3][j-3])
                 won = _gameTable[i][j];
        }
    }
    if (won == 1)
    {
        QMessageBox::information(this, tr("Játék vége!"), tr("A fekete nyerte a játékot!"));
        newGame();
    }
    else if (won == 2)
    {
        QMessageBox::information(this, tr("Játék vége!"), tr("A fehér nyerte a játékot!"));
        newGame();
    }
}

void lovagiTorna::buttonClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = _tableLayout->indexOf(senderButton);
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            _buttonTable[i][j]->setEnabled(false);
        }
    }
    _buttonTable[ _horses[_currentPlayer-1][0] ][ _horses[_currentPlayer-1][1] ]->setEnabled(true);
    _buttonTable[ _horses[_currentPlayer-1][2] ][ _horses[_currentPlayer-1][3] ]->setEnabled(true);
    if (location / 8 == _horses[0][0] && location % 8 == _horses[0][1])
    {
        _selected = location;
        if (_horses[0][0] - 1 >= 0 && _horses[0][1] - 2 >= 0
                && !(_horses[0][0] - 1 == _horses[0][2] && _horses[0][1] - 2 == _horses[0][3])
                && !(_horses[0][0] - 1 == _horses[1][0] && _horses[0][1] - 2 == _horses[1][1])
                && !(_horses[0][0] - 1 == _horses[1][2] && _horses[0][1] - 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] - 1][_horses[0][1] - 2]->setEnabled(true);
        }
        if (_horses[0][0] - 1 >= 0 && _horses[0][1] + 2 <= 7
                && !(_horses[0][0] - 1 == _horses[0][2] && _horses[0][1] + 2 == _horses[0][3])
                && !(_horses[0][0] - 1 == _horses[1][0] && _horses[0][1] + 2 == _horses[1][1])
                && !(_horses[0][0] - 1 == _horses[1][2] && _horses[0][1] + 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] - 1][_horses[0][1] + 2]->setEnabled(true);
        }
        if (_horses[0][0] + 1 <= 7 && _horses[0][1] - 2 >= 0
                && !(_horses[0][0] + 1 == _horses[0][2] && _horses[0][1] - 2 == _horses[0][3])
                && !(_horses[0][0] + 1 == _horses[1][0] && _horses[0][1] - 2 == _horses[1][1])
                && !(_horses[0][0] + 1 == _horses[1][2] && _horses[0][1] - 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] + 1][_horses[0][1] - 2]->setEnabled(true);
        }
        if (_horses[0][0] + 1 <= 7 && _horses[0][1] + 2 <= 7
                && !(_horses[0][0] + 1 == _horses[0][2] && _horses[0][1] + 2 == _horses[0][3])
                && !(_horses[0][0] + 1 == _horses[1][0] && _horses[0][1] + 2 == _horses[1][1])
                && !(_horses[0][0] + 1 == _horses[1][2] && _horses[0][1] + 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] + 1][_horses[0][1] + 2]->setEnabled(true);
        }
        if (_horses[0][0] - 2 >= 0 && _horses[0][1] - 1 >= 0
                && !(_horses[0][0] - 2 == _horses[0][2] && _horses[0][1] - 1 == _horses[0][3])
                && !(_horses[0][0] - 2 == _horses[1][0] && _horses[0][1] - 1 == _horses[1][1])
                && !(_horses[0][0] - 2 == _horses[1][2] && _horses[0][1] - 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] - 2][_horses[0][1] - 1]->setEnabled(true);
        }
        if (_horses[0][0] + 2 <= 7 && _horses[0][1] - 1 >= 0
                && !(_horses[0][0] + 2 == _horses[0][2] && _horses[0][1] - 1 == _horses[0][3])
                && !(_horses[0][0] + 2 == _horses[1][0] && _horses[0][1] - 1 == _horses[1][1])
                && !(_horses[0][0] + 2 == _horses[1][2] && _horses[0][1] - 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] + 2][_horses[0][1] - 1]->setEnabled(true);
        }
        if (_horses[0][0] - 2 >= 0 && _horses[0][1] + 1 <= 7
                && !(_horses[0][0] - 2 == _horses[0][2] && _horses[0][1] + 1 == _horses[0][3])
                && !(_horses[0][0] - 2 == _horses[1][0] && _horses[0][1] + 1 == _horses[1][1])
                && !(_horses[0][0] - 2 == _horses[1][2] && _horses[0][1] + 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] - 2][_horses[0][1] + 1]->setEnabled(true);
        }
        if (_horses[0][0] + 2 <= 7 && _horses[0][1] + 1 <= 7
                && !(_horses[0][0] + 2 == _horses[0][2] && _horses[0][1] + 1 == _horses[0][3])
                && !(_horses[0][0] + 2 == _horses[1][0] && _horses[0][1] + 1 == _horses[1][1])
                && !(_horses[0][0] + 2 == _horses[1][2] && _horses[0][1] + 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][0] + 2][_horses[0][1] + 1]->setEnabled(true);
        }
    }
    else if (location / 8 == _horses[0][2] && location % 8 == _horses[0][3])
    {
        _selected = location;
        if (_horses[0][2] - 1 >= 0 && _horses[0][3] - 2 >= 0
                && !(_horses[0][2] - 1 == _horses[0][0] && _horses[0][3] - 2 == _horses[0][1])
                && !(_horses[0][2] - 1 == _horses[1][0] && _horses[0][3] - 2 == _horses[1][1])
                && !(_horses[0][2] - 1 == _horses[1][2] && _horses[0][3] - 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] - 1][_horses[0][3] - 2]->setEnabled(true);
        }
        if (_horses[0][2] - 1 >= 0 && _horses[0][3] + 2 <= 7
                && !(_horses[0][2] - 1 == _horses[0][0] && _horses[0][3] + 2 == _horses[0][1])
                && !(_horses[0][2] - 1 == _horses[1][0] && _horses[0][3] + 2 == _horses[1][1])
                && !(_horses[0][2] - 1 == _horses[1][2] && _horses[0][3] + 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] - 1][_horses[0][3] + 2]->setEnabled(true);
        }
        if (_horses[0][2] + 1 <= 7 && _horses[0][3] - 2 >= 0
                && !(_horses[0][2] + 1 == _horses[0][0] && _horses[0][3] - 2 == _horses[0][1])
                && !(_horses[0][2] + 1 == _horses[1][0] && _horses[0][3] - 2 == _horses[1][1])
                && !(_horses[0][2] + 1 == _horses[1][2] && _horses[0][3] - 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] + 1][_horses[0][3] - 2]->setEnabled(true);
        }
        if (_horses[0][2] + 1 <= 7 && _horses[0][3] + 2 <= 7
                && !(_horses[0][2] + 1 == _horses[0][0] && _horses[0][3] + 2 == _horses[0][1])
                && !(_horses[0][2] + 1 == _horses[1][0] && _horses[0][3] + 2 == _horses[1][1])
                && !(_horses[0][2] + 1 == _horses[1][2] && _horses[0][3] + 2 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] + 1][_horses[0][3] + 2]->setEnabled(true);
        }
        if (_horses[0][2] - 2 >= 0 && _horses[0][3] - 1 >= 0
                && !(_horses[0][2] - 2 == _horses[0][0] && _horses[0][3] - 1 == _horses[0][1])
                && !(_horses[0][2] - 2 == _horses[1][0] && _horses[0][3] - 1 == _horses[1][1])
                && !(_horses[0][2] - 2 == _horses[1][2] && _horses[0][3] - 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] - 2][_horses[0][3] - 1]->setEnabled(true);
        }
        if (_horses[0][2] + 2 <= 7 && _horses[0][3] - 1 >= 0
                && !(_horses[0][2] + 2 == _horses[0][0] && _horses[0][3] - 1 == _horses[0][1])
                && !(_horses[0][2] + 2 == _horses[1][0] && _horses[0][3] - 1 == _horses[1][1])
                && !(_horses[0][2] + 2 == _horses[1][2] && _horses[0][3] - 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] + 2][_horses[0][3] - 1]->setEnabled(true);
        }
        if (_horses[0][2] - 2 >= 0 && _horses[0][3] + 1 <= 7
                && !(_horses[0][2] - 2 == _horses[0][0] && _horses[0][3] + 1 == _horses[0][1])
                && !(_horses[0][2] - 2 == _horses[1][0] && _horses[0][3] + 1 == _horses[1][1])
                && !(_horses[0][2] - 2 == _horses[1][2] && _horses[0][3] + 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] - 2][_horses[0][3] + 1]->setEnabled(true);
        }
        if (_horses[0][2] + 2 <= 7 && _horses[0][3] + 1 <= 7
                && !(_horses[0][2] + 2 == _horses[0][0] && _horses[0][3] + 1 == _horses[0][1])
                && !(_horses[0][2] + 2 == _horses[1][0] && _horses[0][3] + 1 == _horses[1][1])
                && !(_horses[0][2] + 2 == _horses[1][2] && _horses[0][3] + 1 == _horses[1][3]))
        {
            _buttonTable[_horses[0][2] + 2][_horses[0][3] + 1]->setEnabled(true);
        }
    }
    else if (location / 8 == _horses[1][0] && location % 8 == _horses[1][1])
    {
        _selected = location;
        if (_horses[1][0] - 1 >= 0 && _horses[1][1] - 2 >= 0
                && !(_horses[1][0] - 1 == _horses[0][2] && _horses[1][1] - 2 == _horses[0][3])
                && !(_horses[1][0] - 1 == _horses[0][0] && _horses[1][1] - 2 == _horses[0][1])
                && !(_horses[1][0] - 1 == _horses[1][2] && _horses[1][1] - 2 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] - 1][_horses[1][1] - 2]->setEnabled(true);
        }
        if (_horses[1][0] - 1 >= 0 && _horses[1][1] + 2 <= 7
                && !(_horses[1][0] - 1 == _horses[0][2] && _horses[1][1] + 2 == _horses[0][3])
                && !(_horses[1][0] - 1 == _horses[0][0] && _horses[1][1] + 2 == _horses[0][1])
                && !(_horses[1][0] - 1 == _horses[1][2] && _horses[1][1] + 2 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] - 1][_horses[1][1] + 2]->setEnabled(true);
        }
        if (_horses[1][0] + 1 <= 7 && _horses[1][1] - 2 >= 0
                && !(_horses[1][0] + 1 == _horses[0][2] && _horses[1][1] - 2 == _horses[0][3])
                && !(_horses[1][0] + 1 == _horses[0][0] && _horses[1][1] - 2 == _horses[0][1])
                && !(_horses[1][0] + 1 == _horses[1][2] && _horses[1][1] - 2 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] + 1][_horses[1][1] - 2]->setEnabled(true);
        }
        if (_horses[1][0] + 1 <= 7 && _horses[1][1] + 2 <= 7
                && !(_horses[1][0] + 1 == _horses[0][2] && _horses[1][1] + 2 == _horses[0][3])
                && !(_horses[1][0] + 1 == _horses[0][0] && _horses[1][1] + 2 == _horses[0][1])
                && !(_horses[1][0] + 1 == _horses[1][2] && _horses[1][1] + 2 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] + 1][_horses[1][1] + 2]->setEnabled(true);
        }
        if (_horses[1][0] - 2 >= 0 && _horses[1][1] - 1 >= 0
                && !(_horses[1][0] - 2 == _horses[0][2] && _horses[1][1] - 1 == _horses[0][3])
                && !(_horses[1][0] - 2 == _horses[0][0] && _horses[1][1] - 1 == _horses[0][1])
                && !(_horses[1][0] - 2 == _horses[1][2] && _horses[1][1] - 1 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] - 2][_horses[1][1] - 1]->setEnabled(true);
        }
        if (_horses[1][0] + 2 <= 7 && _horses[1][1] - 1 >= 0
                && !(_horses[1][0] + 2 == _horses[0][2] && _horses[1][1] - 1 == _horses[0][3])
                && !(_horses[1][0] + 2 == _horses[0][0] && _horses[1][1] - 1 == _horses[0][1])
                && !(_horses[1][0] + 2 == _horses[1][2] && _horses[1][1] - 1 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] + 2][_horses[1][1] - 1]->setEnabled(true);
        }
        if (_horses[1][0] - 2 >= 0 && _horses[1][1] + 1 <= 7
                && !(_horses[1][0] - 2 == _horses[0][2] && _horses[1][1] + 1 == _horses[0][3])
                && !(_horses[1][0] - 2 == _horses[0][0] && _horses[1][1] + 1 == _horses[0][1])
                && !(_horses[1][0] - 2 == _horses[1][2] && _horses[1][1] + 1 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] - 2][_horses[1][1] + 1]->setEnabled(true);
        }
        if (_horses[1][0] + 2 <= 7 && _horses[1][1] + 1 <= 7
                && !(_horses[1][0] + 2 == _horses[0][2] && _horses[1][1] + 1 == _horses[0][3])
                && !(_horses[1][0] + 2 == _horses[0][0] && _horses[1][1] + 1 == _horses[0][1])
                && !(_horses[1][0] + 2 == _horses[1][2] && _horses[1][1] + 1 == _horses[1][3]))
        {
            _buttonTable[_horses[1][0] + 2][_horses[1][1] + 1]->setEnabled(true);
        }
    }
    else if (location / 8 == _horses[1][2] && location % 8 == _horses[1][3])
    {
        _selected = location;
        if (_horses[1][2] - 1 >= 0 && _horses[1][3] - 2 >= 0
                && !(_horses[1][2] - 1 == _horses[0][2] && _horses[1][3] - 2 == _horses[0][3])
                && !(_horses[1][2] - 1 == _horses[1][0] && _horses[1][3] - 2 == _horses[1][1])
                && !(_horses[1][2] - 1 == _horses[0][0] && _horses[1][3] - 2 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] - 1][_horses[1][3] - 2]->setEnabled(true);
        }
        if (_horses[1][2] - 1 >= 0 && _horses[1][3] + 2 <= 7
                && !(_horses[1][2] - 1 == _horses[0][2] && _horses[1][3] + 2 == _horses[0][3])
                && !(_horses[1][2] - 1 == _horses[1][0] && _horses[1][3] + 2 == _horses[1][1])
                && !(_horses[1][2] - 1 == _horses[0][0] && _horses[1][3] + 2 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] - 1][_horses[1][3] + 2]->setEnabled(true);
        }
        if (_horses[1][2] + 1 <= 7 && _horses[1][3] - 2 >= 0
                && !(_horses[1][2] + 1 == _horses[0][2] && _horses[1][3] - 2 == _horses[0][3])
                && !(_horses[1][2] + 1 == _horses[1][0] && _horses[1][3] - 2 == _horses[1][1])
                && !(_horses[1][2] + 1 == _horses[0][0] && _horses[1][3] - 2 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] + 1][_horses[1][3] - 2]->setEnabled(true);
        }
        if (_horses[1][2] + 1 <= 7 && _horses[1][3] + 2 <= 7
                && !(_horses[1][2] + 1 == _horses[0][2] && _horses[1][3] + 2 == _horses[0][3])
                && !(_horses[1][2] + 1 == _horses[1][0] && _horses[1][3] + 2 == _horses[1][1])
                && !(_horses[1][2] + 1 == _horses[0][0] && _horses[1][3] + 2 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] + 1][_horses[1][3] + 2]->setEnabled(true);
        }
        if (_horses[1][2] - 2 >= 0 && _horses[1][3] - 1 >= 0
                && !(_horses[1][2] - 2 == _horses[0][2] && _horses[1][3] - 1 == _horses[0][3])
                && !(_horses[1][2] - 2 == _horses[1][0] && _horses[1][3] - 1 == _horses[1][1])
                && !(_horses[1][2] - 2 == _horses[0][0] && _horses[1][3] - 1 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] - 2][_horses[1][3] - 1]->setEnabled(true);
        }
        if (_horses[1][2] + 2 <= 7 && _horses[1][3] - 1 >= 0
                && !(_horses[1][2] + 2 == _horses[0][2] && _horses[1][3] - 1 == _horses[0][3])
                && !(_horses[1][2] + 2 == _horses[1][0] && _horses[1][3] - 1 == _horses[1][1])
                && !(_horses[1][2] + 2 == _horses[0][0] && _horses[1][3] - 1 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] + 2][_horses[1][3] - 1]->setEnabled(true);
        }
        if (_horses[1][2] - 2 >= 0 && _horses[1][3] + 1 <= 7
                && !(_horses[1][2] - 2 == _horses[0][2] && _horses[1][3] + 1 == _horses[0][3])
                && !(_horses[1][2] - 2 == _horses[1][0] && _horses[1][3] + 1 == _horses[1][1])
                && !(_horses[1][2] - 2 == _horses[0][0] && _horses[1][3] + 1 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] - 2][_horses[1][3] + 1]->setEnabled(true);
        }
        if (_horses[1][2] + 2 <= 7 && _horses[1][3] + 1 <= 7
                && !(_horses[1][2] + 2 == _horses[0][2] && _horses[1][3] + 1 == _horses[0][3])
                && !(_horses[1][2] + 2 == _horses[1][0] && _horses[1][3] + 1 == _horses[1][1])
                && !(_horses[1][2] + 2 == _horses[0][0] && _horses[1][3] + 1 == _horses[0][1]))
        {
            _buttonTable[_horses[1][2] + 2][_horses[1][3] + 1]->setEnabled(true);
        }
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 3; j+=2)
            {
                if (_selected / 8 == _horses[i][j] && _selected % 8 == _horses[i][j+1])
                {
                    _horses[i][j] = location / 8;
                    _horses[i][j+1] = location % 8;
                }
            }
        }
        stepGame(location / 8, location % 8);
    }
}

void lovagiTorna::newGameButtonClicked()
{
    newGame();
}

