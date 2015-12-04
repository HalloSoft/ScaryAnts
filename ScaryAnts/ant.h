#ifndef ANT_H
#define ANT_H

#include <QPointF>


class Ant
{
public:
    Ant();

    void setPosition(const QPointF& position) { _position = position;}
    QPointF position() const {return _position;}

    void setSpeed(const QPointF& speed) { _speed = speed;}

    void processNewPosition();

private:
    QPointF _position;
    QPointF _speed;

};

#endif // ANT_H
