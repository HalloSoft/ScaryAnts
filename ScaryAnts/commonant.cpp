#include "commonant.h"

#include "world.h"


#include <QDebug>
#include <QRect>

CommonAnt::CommonAnt(World *world) :
    Ant(world)
{

}

void CommonAnt::processNewPosition()
{
    calculateDirectionAndSpeed();

    QPointF tryPoint = position() + makeVelocityVector(speed(),  direction());

    QRect worldArea = world()->rect();

    if(worldArea.contains(tryPoint.toPoint()))
        setPosition(tryPoint);
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

    setDirection(makeVelocityVector(speed(), QPointF(dx, dy)));
}



void CommonAnt::changeDirection(const QPointF& nextPoint)
{
    QRectF boundingRect = world()->rect();
    QPointF newDirection;

    if((nextPoint.x() < 1) ||(nextPoint.x() > boundingRect.width() - 2))
        newDirection.setX(- direction().x());

    if((nextPoint.y() < 1) ||(nextPoint.y() > boundingRect.height() - 2))
        newDirection.setY( - direction().y());

    setDirection(newDirection);
}
