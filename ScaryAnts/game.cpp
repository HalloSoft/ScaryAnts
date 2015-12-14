#include "game.h"

#include "world.h"

Game::Game(World *world, QObject *parent) :
    QObject(parent),
    _world(world)
{
    Q_CHECK_PTR(_world);


}
void Game::initialize()
{
    int id1 =_world->createAnt(QPoint(200, 2));
    _world->antHash().value(id1)->setSpeed(3);
    int id2 =_world->createAnt(QPoint(220, 2));
    _world->antHash().value(id2)->setSpeed(1.5);
    int id3 =_world->createAnt(QPoint(240, 2));
    _world->antHash().value(id3)->setSpeed(1.5);
    int id4 =_world->createAnt(QPoint(260, 2));
    _world->antHash().value(id4)->setSpeed(3);
    int id5 =_world->createAnt(QPoint(270, 2));
    _world->antHash().value(id5)->setSpeed(1.5);
    int id6 =_world->createAnt(QPoint(300, 2));
    _world->antHash().value(id6)->setSpeed(1.5);

    _world->repaint();
}

void Game::initialize(QList<QPointF> startPoints)
{


    foreach (QPointF startPoint, startPoints)
    {
        _world->createAnt(startPoint);

    }

    initialize();
}

void Game::start()
{
    _world->startGame();
}

