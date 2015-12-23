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
    for(int row = 10; row < _world->height(); row += 50)
    {
        for(int column = 10; column < _world->width(); column += 50)
        {
            int id1 =_world->createAnt(QPoint(column, row), Ant::social);
            _world->antHash().value(id1)->setSpeed(3);
            _world->antHash().value(id1)->setInteractionRadius(30);
        }
    }

//    int id2 =_world->createAnt(QPoint(0, 100), Ant::social);
//    _world->antHash().value(id2)->setSpeed(1.5);
//    _world->antHash().value(id1)->setInteractionRadius(150);

//    int id3 =_world->createAnt(QPoint(0, 200), Ant::social);
//    _world->antHash().value(id3)->setSpeed(1.5);

//    int id4 =_world->createAnt(QPoint(500, 300), Ant::social);
//    _world->antHash().value(id4)->setSpeed(3);
//    _world->antHash().value(id4)->setInteractionRadius(130);

//    int id5 =_world->createAnt(QPoint(280, 2), Ant::social);
//    _world->antHash().value(id5)->setSpeed(1.5);
//    _world->antHash().value(id5)->setInteractionRadius(80);

//    int id6 =_world->createAnt(QPoint(300, 2), Ant::social);
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

