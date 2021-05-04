#ifndef LABYRINTHLOADMOCK_H
#define LABYRINTHLOADMOCK_H

#include "labyrinthload.h"
#include "QtDebug"

class LabyrinthLoadMock : public LabyrinthLoad
{
    public:
        bool loadSuccess(QString difficulty)
        {
            difficulty = "easy";
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
            qDebug() << difficulty << "map loaded with size: " << _mapSize << ", containing values: ";
            for (int i = 0; i < _mapSize*_mapSize; i++)
                qDebug() << _map[i] << " ";
            qDebug() << endl;
            return true;
        }

    private:
        int _mapSize;
        QVector<QString> _map;
};

#endif // LABYRINTHLOADMOCK_H
