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



    if(isPositionPossible(tryPoint))
        setPosition(tryPoint);
    else
    {
       changeDirectionOnBarrier(tryPoint);
       //setPosition(position() + QPointF(1,1));
    }
}

void SocialAnt::calculateDirectionAndSpeed()
{
    const QPointF directionVector = generateRandomDirection();

    // check neibourhood
    AntList allAntsInRange = antsInRange(interactionRadius());

    QPointF newDirection;

    if(allAntsInRange.count() > 0)
    {
        QPointF socialDirection = interationDirection(allAntsInRange);
        newDirection = makeVelocityVector(speed(), socialDirection);
    }
    else
        newDirection = makeVelocityVector(speed(), directionVector);

    setDirection(newDirection);
}

void SocialAnt::changeDirectionOnBarrier(const QPointF& nextPoint)
{
    Q_UNUSED(nextPoint);
//    QRectF boundingRect = world()->rect();
//    QPointF newDirection;

//    if((nextPoint.x() < 1) ||(nextPoint.x() > boundingRect.width() - 2))
//        newDirection.setX( - direction().x());

//    if((nextPoint.y() < 1) ||(nextPoint.y() > boundingRect.height() - 2))
//        newDirection.setY( - direction().y());

    QPointF newDirection = -direction() + QPointF(0, 1);
    newDirection *= 2;
    setDirection(newDirection);
}

AntList SocialAnt::antsInRange(double range) const
{
    AntList result;

    AntHash antHash = world()->antHash();

    foreach(quint64 antId, antHash.keys())
    {
        Ant *otherAnt = antHash.value(antId);

        bool isNotMe = (this != otherAnt);

        double distanceToOther = distance(otherAnt, true);

        if(isNotMe && (distanceToOther <= range))
            result << otherAnt;
    }

    return result;
}

Ant* SocialAnt::nearestSibling(AntList antsInRange) const
{
    Ant *nearestSibling  = nullptr;

    int minDistance = std::numeric_limits<int>::max();


    foreach(Ant *otherAnt, antsInRange)
    {
        float distanceToOtherAnt = distance(otherAnt, true);

        if(distanceToOtherAnt < minDistance)
        {
            minDistance = distanceToOtherAnt;
            nearestSibling = otherAnt;
        }
    }

    return nearestSibling;
}

bool SocialAnt::isPositionPossible(const QPointF position) const
{
    bool isPossible = true;

    QRectF worldArea = world()->rect();

    // check world borders
    if(!worldArea.contains(position.toPoint()))
        isPossible = false;

    // check other ants
    AntList allAntsInRange = antsInRange(interactionRadius());
    Ant *nearestAnt = nearestSibling(allAntsInRange);
    if(nearestAnt)
    {
        double distanceToNearest = distance(nearestAnt, true);
        if(distanceToNearest <= privacyRadius())
            isPossible = false;
    }

    return isPossible;
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

QPointF SocialAnt::interationDirection(AntList antsInRange) const
{
    QPointF resultVector;

    foreach(Ant *neighbourAnt, antsInRange)
        resultVector += directionToFirend(neighbourAnt);

    return resultVector;
}

QPointF SocialAnt::generateRandomDirection() const
{
    float dxStaticPart = direction().x() * 1;
    float dyStaticPart = direction().y() * 1;

    float dxRandomPart = (randomFactor() * 3);
    float dyRandomPart = (randomFactor() * 3);

    float dx = dxStaticPart + dxRandomPart;
    float dy = dyStaticPart + dyRandomPart;

    return QPointF(dx, dy);

}
