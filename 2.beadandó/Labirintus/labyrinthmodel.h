#ifndef LABYRINTHMODEL_H
#define LABYRINTHMODEL_H

#include <QObject>
#include "QTimer"
#include "QTime"
#include "labyrinthload.h"

class labyrinthModel : public QObject
{
    Q_OBJECT
public:
    explicit labyrinthModel(QObject *parent = nullptr);
    void calculateVisibility(QString difficulty);
    int player() { return _player;}
    QVector<int> visiblePlatforms() { return _visiblePlatforms;}
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void resetFirstMove() { _firstMove = false; }
    void resetTime() { _totalTime = 0; }
    void stopTime();
    void startTime();
    bool checkFinish();

    QTime* _time;
    QTimer* _timer;
    int _totalTime;

private:
    int _player;
    bool _firstMove = false;
    QVector<int> _visiblePlatforms;
    LabyrinthLoad* _labyrinthLoad;

};

#endif // LABYRINTHMODEL_H
