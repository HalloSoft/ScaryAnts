#ifndef ANT_H
#define ANT_H

#include <QPointF>

#include "world.h"


class Ant
{
public:
    Ant(World *world);

    World* world() const {return _world;}

    void    setPosition(const QPointF& position) { _position = position;}
    QPointF position() const {return _position;}

    void    setSpeed(float speed) { _speed = speed;}
    float   speed() const { return _speed;}

    void    setDirection(const QPointF& dircetion) {_direction = dircetion;}
    QPointF direction() const {return _direction;}

    void    setInteractionRadius(float interactionRadius) {_interactionRadius = interactionRadius;}
    float   interactionRadius() const { return _interactionRadius;}

    virtual void processNewPosition() = 0;

    double distance(Ant* other, bool exactCalculation = false) const;

protected:

    QPointF makeVelocityVector(float speed, const QPointF& direction);
    float randomFactor() const;

private:
    World   *_world;
    QPointF _position;
    QPointF _direction;
    float   _speed;
    float   _interactionRadius;

    quint64 _id; //TODO: is it neccessary
};

#endif // ANT_H
