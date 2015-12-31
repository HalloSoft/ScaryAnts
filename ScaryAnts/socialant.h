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

    AntList antsInRange(double range) const;
    Ant *nearestSibling(AntList antsInRange) const;

    bool    isPositionPossible(const QPointF position) const;
    QPointF directionToFirend(Ant* other) const;
    QPointF interationDirection(Ant* other) const;
    QPointF interationDirection(AntList antsInRange) const;
    QPointF generateRandomDirection() const;

};

#endif // SOCIALANT_H
