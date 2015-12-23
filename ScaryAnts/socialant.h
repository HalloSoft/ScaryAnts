#ifndef SOCIALANT_H
#define SOCIALANT_H

#include "ant.h"

class SocialAnt : public Ant
{
public:
    SocialAnt(World *world);

    virtual void processNewPosition();

private:
    void calculateDirectionAndSpeed();
    void changeDirectionOnBarrier(const QPointF &nextPoint);

    Ant *nearestSiblingNear(double maxDistance) const;

    QPointF directionToFirend(Ant* other) const;
    QPointF interationDirection(Ant* other) const;

};

#endif // SOCIALANT_H
