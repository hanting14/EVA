#ifndef LABYRINTHLOAD_H
#define LABYRINTHLOAD_H

#include "QString"
#include "QFile"
#include "QTextStream"
#include "QVector"

class LabyrinthLoad
{
public:
    LabyrinthLoad();
    bool loadSucces(QString difficulty);
    int mapSize() { return _mapSize;}
    QVector<QString> getMap() { return _map;}

private:
    int _mapSize;
    QVector<QString> _map;
};

#endif // LABYRINTHLOAD_H
