#ifndef COMMONANT_H
#define COMMONANT_H

#include "ant.h"


class CommonAnt : public Ant
{
public:
    CommonAnt(World *world);

    virtual void processNewPosition();

private:

    void  calculateDirectionAndSpeed();

    void changeDirection(const QPointF &nextPoint);

};

#endif // COMMONANT_H
