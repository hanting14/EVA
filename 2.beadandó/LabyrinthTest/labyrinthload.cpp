#include "labyrinthload.h"

LabyrinthLoad::LabyrinthLoad()
{

}

bool LabyrinthLoad::loadSucces(QString difficulty)
{
    QFile file(":/maps/" + difficulty + ".sav");
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QTextStream stream(&file);
    _mapSize = stream.readLine().toInt();
    _map.clear();
    // soronként beolvassuk az adatokat a fájlból
    QString tmp;
    for (int i = 0; i < _mapSize * _mapSize; i++)
    {
        stream >> tmp;
        _map.push_back(tmp);
    }
    file.close();
    return true;
}
