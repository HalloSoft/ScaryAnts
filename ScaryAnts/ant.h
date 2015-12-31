#ifndef ANT_H
#define ANT_H

#include <QHash>
#include <QPointF>

//#include "world.h"
class World;

class Ant
{
public:
    enum AntType{ common, social};

    Ant(World *world);

    World* world() const {return _world;}

    void    setPosition(const QPointF& position) { _position = position;}
    QPointF position() const {return _position;}

    void    setSizeRadius(float sizeRadius) {_size =sizeRadius;}
    float   sizeRadus() const {return _size;}

    void    setSpeed(float speed) { _speed = speed;}
    float   speed() const { return _speed;}

    void    setDirection(const QPointF& dircetion) {_direction = dircetion;}
    QPointF direction() const {return _direction;}

    void    setInteractionRadius(float interactionRadius) {_interactionRadius = interactionRadius;}
    float   interactionRadius() const { return _interactionRadius;}

    void    setPrivacyRadius(float privacyRadius) {_privacyRadius = privacyRadius;}
    float   privacyRadius() const {return _privacyRadius;}

    virtual void processNewPosition() = 0;

    double distance(Ant* other, bool exactCalculation = false) const;

protected:


    QPointF makeVelocityVector(float speed, const QPointF& direction);
    float randomFactor() const;

private:
    World   *_world;
    QPointF _position;
    QPointF _direction;
    float   _size;
    float   _speed;
    float   _interactionRadius;
    float   _privacyRadius;

    quint64 _id; //TODO: is it neccessary?
};

typedef QHash<quint64,Ant*> AntHash;
typedef QList<Ant*> AntList;
#endif // ANT_H
