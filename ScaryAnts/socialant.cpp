#include "socialant.h"

#include <QRectF>
#include <QtDebug>

SocialAnt::SocialAnt(World *world) :
    Ant(world)
{

}

void SocialAnt::processNewPosition()
{
    calculateDirectionAndSpeed();

    QPointF tryPoint = _position + makeVelocityVector(speed(),  _direction);

    QRectF worldArea = _world->rect();

    if(worldArea.contains(tryPoint.toPoint()))
        _position = tryPoint;
    else
       changeDirectionOnBarrier(tryPoint);
}

void SocialAnt::calculateDirectionAndSpeed()
{
    //modify direction
    float dxStaticPart = direction().x() * 2;
    float dyStaticPart = direction().y() * 2;

    float dxRandomPart = (randomFactor() * 1);
    float dyRandomPart = (randomFactor() * 1);

    float dx = dxStaticPart + dxRandomPart;
    float dy = dyStaticPart + dyRandomPart;

    const QPointF directionVector = QPointF(dx, dy);

    isSiblingNear(10);

    _direction = makeVelocityVector(speed(), directionVector);
}

void SocialAnt::changeDirectionOnBarrier(const QPointF& nextPoint)
{
    QRectF boundingRect = _world->rect();

    if((nextPoint.x() < 1) ||(nextPoint.x() > boundingRect.width() - 2))
        _direction.setX(-_direction.x());

    if((nextPoint.y() < 1) ||(nextPoint.y() > boundingRect.height() - 2))
        _direction.setY( -_direction.y());
}

bool SocialAnt::isSiblingNear(double maxDistance) const
{
    bool result = false;

    QHash<quint64, Ant*>::const_iterator i;
    for (i = _world->antHash().constBegin(); i != _world->antHash().constEnd(); ++i)
    {
        Ant *ant = i.value();

        if(this != ant)
        {
            if(distance(ant) < maxDistance)
            {
                qDebug() << "Alert!!!";
            }
        }
    }

    return result;
}
