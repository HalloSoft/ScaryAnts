#include "ant.h"

Ant::Ant()
{

}

void Ant::processNewPosition()
{
    _position += _speed;
}

