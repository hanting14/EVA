#ifndef LOVAGITORNA_H
#define LOVAGITORNA_H

#include <QWidget>
#include "QGridLayout"
#include "QPushButton"
#include "QMessageBox"

class lovagiTorna : public QWidget
{
    Q_OBJECT

public:
    lovagiTorna(QWidget *parent = nullptr);
    ~lovagiTorna();

private slots:
    void buttonClicked();
    void newGameButtonClicked();

private:

    void generateField();
    void newGame();
    void stepGame(int x, int y);
    void checkGame();

    int _currentPlayer;
    QGridLayout* _tableLayout;
    QVBoxLayout* _mainLayout;
    QPushButton* _newGameButton;
    QVector<QVector<QPushButton*> > _buttonTable;
    int** _gameTable;
    int** _horses;
    bool** _firstMove;
    int _selected;
};
#endif // LOVAGITORNA_H
