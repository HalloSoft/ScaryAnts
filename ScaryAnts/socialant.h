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

    bool isSiblingNear(double maxDistance) const;

};

#endif // SOCIALANT_H
