#include "labyrinthmodel.h"

labyrinthModel::labyrinthModel(QObject *parent) : QObject(parent)
{
    _labyrinthLoad = new LabyrinthLoad();
    _time = new QTime();
    _timer = new QTimer();
    _totalTime = 0;
}

void labyrinthModel::calculateVisibility(QString difficulty)
{

    _visiblePlatforms.clear();
    if (difficulty == "easy" && _labyrinthLoad->loadSucces("easy"))
    {
        if (!_firstMove)
            _player = _labyrinthLoad->mapSize()*(_labyrinthLoad->mapSize()-1);
        for (int i = _player-2-(2*_labyrinthLoad->mapSize()); i<_player+(2*_labyrinthLoad->mapSize()); i+=_labyrinthLoad->mapSize())
        {
            for (int j = i; j<=i+4; ++j)
            {
                if (_labyrinthLoad->getMap().size() > j && (j%_labyrinthLoad->mapSize()) <= _player%_labyrinthLoad->mapSize()+2
                        && j%_labyrinthLoad->mapSize() >= _player%_labyrinthLoad->mapSize()-2)
                    _visiblePlatforms.push_back(j);
            }
        }
        if (_visiblePlatforms.contains(_player-1)
                && _visiblePlatforms.contains(_player-2)
                && _labyrinthLoad->getMap()[_player-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+1)
                && _visiblePlatforms.contains(_player+2)
                && _labyrinthLoad->getMap()[_player+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2));
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1) && _labyrinthLoad->getMap()[_player-1] == "f"
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1) && _labyrinthLoad->getMap()[_player+1] == "f"
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1) && _labyrinthLoad->getMap()[_player-1] == "f"
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1) && _labyrinthLoad->getMap()[_player+1] == "f"
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1-(2*_labyrinthLoad->mapSize())));
        }


        if (_visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+1+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-1-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-1+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+1-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
        }


        if (_visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+2+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+1+(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-2-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-1-(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-2+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-1+(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+2-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+1-(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
        }

        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize())+1)
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())+1));
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize())-1)
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())-1));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize())+1)
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())+1));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize())-1)
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())-1));
        }


        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-2)
                && _visiblePlatforms.contains(_player-1)
                && _labyrinthLoad->getMap()[_player-1] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-_labyrinthLoad->mapSize())-2);
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-2)
                && _visiblePlatforms.contains(_player-1)
                && _labyrinthLoad->getMap()[_player-1] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+_labyrinthLoad->mapSize())-2);
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+2)
                && _visiblePlatforms.contains(_player+1)
                && _labyrinthLoad->getMap()[_player+1] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-_labyrinthLoad->mapSize())+2);
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+2)
                && _visiblePlatforms.contains(_player+1)
                && _labyrinthLoad->getMap()[_player+1] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+_labyrinthLoad->mapSize())+2);
        }
    }
    else if (difficulty == "medium" && _labyrinthLoad->loadSucces("medium"))
    {
        if (!_firstMove)
            _player = _labyrinthLoad->mapSize()*(_labyrinthLoad->mapSize()-1);
        for (int i = _player-2-(2*_labyrinthLoad->mapSize()); i<_player+(2*_labyrinthLoad->mapSize()); i+=_labyrinthLoad->mapSize())
        {
            for (int j = i; j<=i+4; ++j)
            {
                if (_labyrinthLoad->getMap().size() > j && (j%_labyrinthLoad->mapSize()) <= _player%_labyrinthLoad->mapSize()+2
                        && j%_labyrinthLoad->mapSize() >= _player%_labyrinthLoad->mapSize()-2)
                    _visiblePlatforms.push_back(j);
            }
        }
        if (_visiblePlatforms.contains(_player-1)
                && _visiblePlatforms.contains(_player-2)
                && _labyrinthLoad->getMap()[_player-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+1)
                && _visiblePlatforms.contains(_player+2)
                && _labyrinthLoad->getMap()[_player+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2));
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1) && _labyrinthLoad->getMap()[_player-1] == "f"
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1) && _labyrinthLoad->getMap()[_player+1] == "f"
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1) && _labyrinthLoad->getMap()[_player-1] == "f"
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1) && _labyrinthLoad->getMap()[_player+1] == "f"
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1-(2*_labyrinthLoad->mapSize())));
        }


        if (_visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+1+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-1-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-1+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+1-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
        }


        if (_visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+2+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+1+(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-2-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-1-(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-2+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-1+(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+2-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+1-(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
        }

        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize())+1)
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())+1));
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize())-1)
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())-1));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize())+1)
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())+1));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize())-1)
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())-1));
        }


        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-2)
                && _visiblePlatforms.contains(_player-1)
                && _labyrinthLoad->getMap()[_player-1] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-_labyrinthLoad->mapSize())-2);
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-2)
                && _visiblePlatforms.contains(_player-1)
                && _labyrinthLoad->getMap()[_player-1] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+_labyrinthLoad->mapSize())-2);
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+2)
                && _visiblePlatforms.contains(_player+1)
                && _labyrinthLoad->getMap()[_player+1] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-_labyrinthLoad->mapSize())+2);
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+2)
                && _visiblePlatforms.contains(_player+1)
                && _labyrinthLoad->getMap()[_player+1] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+_labyrinthLoad->mapSize())+2);
        }
    }
    else if (difficulty == "hard" && _labyrinthLoad->loadSucces("hard"))
    {
        if (!_firstMove)
            _player = _labyrinthLoad->mapSize()*(_labyrinthLoad->mapSize()-1);
        for (int i = _player-2-(2*_labyrinthLoad->mapSize()); i<_player+(2*_labyrinthLoad->mapSize()); i+=_labyrinthLoad->mapSize())
        {
            for (int j = i; j<=i+4; ++j)
            {
                if (_labyrinthLoad->getMap().size() > j && (j%_labyrinthLoad->mapSize()) <= _player%_labyrinthLoad->mapSize()+2
                        && j%_labyrinthLoad->mapSize() >= _player%_labyrinthLoad->mapSize()-2)
                    _visiblePlatforms.push_back(j);
            }
        }
        if (_visiblePlatforms.contains(_player-1)
                && _visiblePlatforms.contains(_player-2)
                && _labyrinthLoad->getMap()[_player-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+1)
                && _visiblePlatforms.contains(_player+2)
                && _labyrinthLoad->getMap()[_player+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2));
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1) && _labyrinthLoad->getMap()[_player-1] == "f"
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1) && _labyrinthLoad->getMap()[_player+1] == "f"
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1) && _labyrinthLoad->getMap()[_player-1] == "f"
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1+_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-1+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1) && _labyrinthLoad->getMap()[_player+1] == "f"
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()) && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1-_labyrinthLoad->mapSize()));
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+1-(2*_labyrinthLoad->mapSize())));
        }


        if (_visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+1+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-1-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-1+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-1+_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+1-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+1-_labyrinthLoad->mapSize()] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
        }


        if (_visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+2+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+1+(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-2-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-1-(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2-(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player-2+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player-2+_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player-1+(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player-2+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-1+(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-2+(2*_labyrinthLoad->mapSize())));
        }
        if (_visiblePlatforms.contains(_player+2-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2-_labyrinthLoad->mapSize())
                && _visiblePlatforms.contains(_player+1-(2*_labyrinthLoad->mapSize()))
                && _visiblePlatforms.contains(_player+2+(2*_labyrinthLoad->mapSize()))
                && _labyrinthLoad->getMap()[_player+2-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+1-(2*_labyrinthLoad->mapSize())] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+2-(2*_labyrinthLoad->mapSize())));
        }

        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize())+1)
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())+1));
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player+(2*_labyrinthLoad->mapSize())-1)
                && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+(2*_labyrinthLoad->mapSize())-1));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize())+1)
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())+1));
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player-(2*_labyrinthLoad->mapSize())-1)
                && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize())
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-(2*_labyrinthLoad->mapSize())-1));
        }


        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()-2)
                && _visiblePlatforms.contains(_player-1)
                && _labyrinthLoad->getMap()[_player-1] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-_labyrinthLoad->mapSize())-2);
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-1) && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()-2)
                && _visiblePlatforms.contains(_player-1)
                && _labyrinthLoad->getMap()[_player-1] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+_labyrinthLoad->mapSize())-2);
        }
        if (_visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player-_labyrinthLoad->mapSize()+2)
                && _visiblePlatforms.contains(_player+1)
                && _labyrinthLoad->getMap()[_player+1] == "f"
                && _labyrinthLoad->getMap()[_player-_labyrinthLoad->mapSize()+1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player-_labyrinthLoad->mapSize())+2);
        }
        if (_visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+1) && _visiblePlatforms.contains(_player+_labyrinthLoad->mapSize()+2)
                && _visiblePlatforms.contains(_player+1)
                && _labyrinthLoad->getMap()[_player+1] == "f"
                && _labyrinthLoad->getMap()[_player+_labyrinthLoad->mapSize()-1] == "f")
        {
            _visiblePlatforms.remove(_visiblePlatforms.indexOf(_player+_labyrinthLoad->mapSize())+2);
        }
}
}
void labyrinthModel::moveUp()
{
    if ((_player / _labyrinthLoad->mapSize()) - 1 >= 0 && _labyrinthLoad->getMap()[_player - _labyrinthLoad->mapSize()] != "f")
    {
        _player -= _labyrinthLoad->mapSize();
        _firstMove = true;
    }
}

void labyrinthModel::moveDown()
{
    if (_player / _labyrinthLoad->mapSize() + 1 < _labyrinthLoad->mapSize() && _labyrinthLoad->getMap()[_player + _labyrinthLoad->mapSize()] != "f")
    {
        _player += _labyrinthLoad->mapSize();
        _firstMove = true;
    }
}

void labyrinthModel::moveLeft()
{
    if (_player % _labyrinthLoad->mapSize() - 1 >= 0 && _labyrinthLoad->getMap()[_player - 1] != "f")
    {
        _player--;
        _firstMove = true;
    }
}

void labyrinthModel::moveRight()
{
    if (_player % _labyrinthLoad->mapSize() + 1  < _labyrinthLoad->mapSize() && _labyrinthLoad->getMap()[_player + 1] != "f")
    {
        _player++;
        _firstMove = true;
    }
}

void labyrinthModel::stopTime()
{
    _totalTime += _time->elapsed();
    _timer->stop();
}

void labyrinthModel::startTime()
{
    _time->start();
    _timer->start(1000);
}

bool labyrinthModel::checkFinish()
{
    return _player == _labyrinthLoad->mapSize()-1;
}
