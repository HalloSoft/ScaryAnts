#include "ant.h"

//#include "world.h"

#include <cmath>

using namespace std;

Ant::Ant(World *world) :
    _world(world),
    _speed(1),
    _interactionRadius(50)
{

}

QPointF Ant::makeVelocityVector(float speed, const QPointF &direction)
{
    double currentAbsValue = sqrt(pow(direction.x(), 2) + pow(direction.y(), 2));

    double factor = speed / currentAbsValue;

    QPointF result = QPointF(direction.x() *factor, direction.y() * factor);

    return result;
}

float Ant::randomFactor() const
{
    const float random = ((float)qrand() - RAND_MAX / 2) / (RAND_MAX / 2);
    return random;
}

double Ant::distance(Ant *other, bool exactCalculation) const
{
    double result = 0;
    if(this != other)
    {
        QPointF difference = this->position() - other->position();

        if(exactCalculation)
            result = sqrt(pow(difference.x(), 2) + pow(difference.y(), 2));
        else
            result = difference.manhattanLength();
    }

    return result;
}

