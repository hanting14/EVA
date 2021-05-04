#ifndef LABYRINTHWIDGET_H
#define LABYRINTHWIDGET_H

#include <QWidget>
#include "labyrinthload.h"
#include "labyrinthmodel.h"
#include "QLayout"
#include "QPushButton"
#include "QPainter"
#include "QLabel"
#include "QStatusBar"

class labyrinthWidget : public QWidget
{
    Q_OBJECT

public:
    labyrinthWidget(QWidget *parent = nullptr);
    ~labyrinthWidget();

protected:
    void paintEvent(QPaintEvent* );
    void keyPressEvent(QKeyEvent *event);

private slots:
    void showEasyLabyrinth();
    void showMediumLabyrinth();
    void showHardLabyrinth();
    void showMenu();
    void modelTimeStop();
    void modelCheckFinish();
    void updateTimeLabel();

private:
    QGridLayout* _gridLayout;
    QPushButton* _easyLabyrinthButton;
    QPushButton* _mediumLabyrinthButton;
    QPushButton* _hardLabyrinthButton;
    QPushButton* _backButton;
    QPushButton* _pauseButton;
    QLabel* _timerLabel;
    LabyrinthLoad* _labyrinthLoad;
    labyrinthModel* _labyrinthModel;
    bool* _labyrintsLoaded;
    bool _stop;
};
#endif // LABYRINTHWIDGET_H
