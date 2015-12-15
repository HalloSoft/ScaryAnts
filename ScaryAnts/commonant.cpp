#include "commonant.h"


#include <QDebug>
#include <QRect>

CommonAnt::CommonAnt(World *world) :
    Ant(world)
{

}

void CommonAnt::processNewPosition()
{
    calculateDirectionAndSpeed();

    QPointF tryPoint = _position + makeVelocityVector(speed(),  _direction);

    QRect worldArea = _world->rect();

    if(worldArea.contains(tryPoint.toPoint()))
        _position = tryPoint;
    else
       changeDirection(tryPoint);
}

void CommonAnt::calculateDirectionAndSpeed()
{

    //modify direction
    float dxStaticPart = direction().x() * 2;
    float dyStaticPart = direction().y() * 2;

    float dxRandomPart = (randomFactor() * 1);
    float dyRandomPart = (randomFactor() * 1);

    float dx = dxStaticPart + dxRandomPart;
    float dy = dyStaticPart + dyRandomPart;

    _direction = makeVelocityVector(speed(), QPointF(dx, dy));
}



void CommonAnt::changeDirection(const QPointF& nextPoint)
{
    QRectF boundingRect = _world->rect();

    if((nextPoint.x() < 1) ||(nextPoint.x() > boundingRect.width() - 2))
        _direction.setX(-_direction.x());

    if((nextPoint.y() < 1) ||(nextPoint.y() > boundingRect.height() - 2))
        _direction.setY( -_direction.y());
}
