#include "socialant.h"

#include "world.h"

#include <limits>
#include <QRectF>
#include <QtDebug>

SocialAnt::SocialAnt(World *world) :
    Ant(world)
{

}

void SocialAnt::processNewPosition()
{
    calculateDirectionAndSpeed();

    QPointF tryPoint = position() + makeVelocityVector(speed(),  direction());

    QRectF worldArea = world()->rect();

    if(worldArea.contains(tryPoint.toPoint()))
        setPosition(tryPoint);
    else
       changeDirectionOnBarrier(tryPoint);
}

void SocialAnt::calculateDirectionAndSpeed()
{
    const QPointF directionVector = generateRandomDirection();

    // chack neibourhood
    Ant *nearestAnt = nearestSibling(interactionRadius());
    QPointF newDirection;
    if(nearestAnt)
    {
        QPointF socialDirection = interationDirection(nearestAnt);
        newDirection = makeVelocityVector(speed(), socialDirection);
    }
    else
        newDirection = makeVelocityVector(speed(), directionVector);

    setDirection(newDirection);
}

void SocialAnt::changeDirectionOnBarrier(const QPointF& nextPoint)
{
    QRectF boundingRect = world()->rect();
    QPointF newDirection;

    if((nextPoint.x() < 1) ||(nextPoint.x() > boundingRect.width() - 2))
        newDirection.setX( - direction().x());

    if((nextPoint.y() < 1) ||(nextPoint.y() > boundingRect.height() - 2))
        newDirection.setY( - direction().y());

    setDirection(newDirection);
}

Ant* SocialAnt::nearestSibling(double maxDistance) const
{
    Ant *nearestSibling  = nullptr;

    int minDistance = std::numeric_limits<int>::max();

    AntHash antHash = world()->antHash();

    foreach(quint64 antId, antHash.keys())
    {
        Ant *otherAnt = antHash.value(antId);

        float distanceToOtherAnt = distance(otherAnt, true);

        bool isOtherAndThisIdentical = (this == otherAnt);
        bool isOtherInRange = (distanceToOtherAnt <= maxDistance);

        if(!isOtherAndThisIdentical && isOtherInRange)
        {
            if(distanceToOtherAnt < minDistance)
            {
                minDistance = distanceToOtherAnt;
                nearestSibling = otherAnt;
            }
        }
    }

    return nearestSibling;
}

QPointF SocialAnt::directionToFirend(Ant *other) const
{
    return other->position() - position();
}

QPointF SocialAnt::interationDirection(Ant *other) const
{
    QPointF resultVector = directionToFirend(other);

    if(distance(other, true) < privacyRadius())
        resultVector = -resultVector;

    return resultVector;
}

QPointF SocialAnt::generateRandomDirection() const
{
    float dxStaticPart = direction().x() * 1;
    float dyStaticPart = direction().y() * 1;

    float dxRandomPart = (randomFactor() * 1);
    float dyRandomPart = (randomFactor() * 1);

    float dx = dxStaticPart + dxRandomPart;
    float dy = dyStaticPart + dyRandomPart;

    return QPointF(dx, dy);

}
