#ifndef ANT_H
#define ANT_H

#include <QPointF>

class World;


class Ant
{
public:
    Ant(World *world);

    void    setPosition(const QPointF& position) { _position = position;}
    QPointF position() const {return _position;}

    void    setSpeed(float speed) { _speed = speed;}
    float   speed() const { return _speed;}

    void    setDirection(const QPointF& dircetion) {_direction = dircetion;}
    QPointF direction() const {return _direction;}

    virtual void processNewPosition() = 0;

protected:
    World   *_world;
    QPointF _position;
    QPointF _direction;
    float   _speed;

};

#endif // ANT_H
