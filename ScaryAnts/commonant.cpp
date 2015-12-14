#include "commonant.h"

#include "world.h"

#include <QtCore>
#include <QDebug>
#include <QRect>

CommonAnt::CommonAnt(World *world) :
    Ant(world)
{

}

void CommonAnt::processNewPosition()
{
    calculateDirectionAndSpeed();

    QPointF tryPoint = _position + newAbsolute(_speed,  _direction);

    QRect worldArea = _world->rect();

    if(worldArea.contains(tryPoint.toPoint()))
        _position = tryPoint;
    else
       changeDirection(tryPoint);
}

void CommonAnt::calculateDirectionAndSpeed()
{

    //modify direction
    float dxStaticPart = direction().x() * 1;
    float dyStaticPart = direction().y() * 1;

    float dxRandomPart = (randomFactor() * 1);
    float dyRandomPart = (randomFactor() * 1);

    float dx = dxStaticPart + dxRandomPart;
    float dy = dyStaticPart + dyRandomPart;

    _direction = newAbsolute(speed(), QPointF(dx, dy));
}

float CommonAnt::randomFactor() const
{
    const float random = ((float)qrand() - RAND_MAX /2) / (RAND_MAX / 2);
    return random;
}

QPointF CommonAnt::newAbsolute(float speed, const QPointF &direction)
{
    double currentAbsValue = qSqrt(direction.x() * direction.x() + direction.y() * direction.y());

    double factor = speed / currentAbsValue;

    QPointF result = QPointF(direction.x() *factor, direction.y() * factor);

    return result;
}

void CommonAnt::changeDirection(const QPointF& nextPoint)
{
    QRectF boundingRect = _world->rect();

    if((nextPoint.x() < 1) ||(nextPoint.x() > boundingRect.width() - 2))
        _direction.setX(-_direction.x());

    if((nextPoint.y() < 1) ||(nextPoint.y() > boundingRect.height() - 2))
        _direction.setY( -_direction.y());
}
