#ifndef GAME_H
#define GAME_H

#include "ant.h"

#include <QWidget>


class World;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(World *world, QObject *parent = 0);

    void initialize();
    void initialize(QList<QPointF> startPoints);

signals:

public slots:
    void start();
    void stop();

private:
    World *_world;

};

#endif // GAME_H
