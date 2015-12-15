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
    int id1 =_world->createAnt(QPoint(100, 2));
    _world->antHash().value(id1)->setSpeed(3);
    int id2 =_world->createAnt(QPoint(100, 200));
    _world->antHash().value(id2)->setSpeed(1.5);
    int id3 =_world->createAnt(QPoint(400, 2));
    _world->antHash().value(id3)->setSpeed(1.5);
    int id4 =_world->createAnt(QPoint(400, 200));
    _world->antHash().value(id4)->setSpeed(3);
//    int id5 =_world->createAnt(QPoint(280, 2));
//    _world->antHash().value(id5)->setSpeed(1.5);
//    int id6 =_world->createAnt(QPoint(300, 2));
//    _world->antHash().value(id6)->setSpeed(1.5);

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

