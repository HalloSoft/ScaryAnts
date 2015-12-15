#include "world.h"

#include "commonant.h"
#include "socialant.h"

#include <cstdlib>
#include <QDebug>
#include <QPainter>
#include <QTime>

const int World::interval = 50;  // milliseconds

World::World(QWidget *parent) :
    QWidget(parent),
    _gameStarted(false)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec() * 1000);
    startTimer(interval);

}

void World::startGame()
{
   _gameStarted = true;
}

void World::stopGame()
{
   _gameStarted = false;
}

quint64 World::createAnt(const QPointF startPoint )
{
    QList<quint64> idList =_antHash.keys();
    quint64 newId = 0;

    if(!idList.isEmpty())
    {
        qSort(idList);
        quint64 maxId = idList.last();

        newId = maxId + 1;
    }

    //Ant *newAnt = new CommonAnt(this);
    Ant *newAnt = new SocialAnt(this);
    newAnt->setPosition(startPoint);

    _antHash.insert(newId, newAnt);

    return newId;
}

void World::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.eraseRect(rect());

    painter.fillRect(rect(), Qt::darkGreen);

    drawAnts(&painter);
}

void World::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if(_gameStarted)
        repaint();
}

void World::drawAnts(QPainter *painter)
{
    foreach(quint64 id, _antHash.keys())
    {
        Ant *ant = _antHash.value(id);
        drawAnt(painter, ant);
        ant->processNewPosition();

    }
}

void World::drawAnt(QPainter *painter, Ant *ant)
{
    painter->setBrush(Qt::black);
    painter->setPen(Qt::darkCyan);

    QPointF position = ant->position();
    painter->drawEllipse(position, 5, 5);


    //qDebug() << "Draw ant at:" << position << "with speed" << ant->speed();
    //qDebug() << "Rand:" << qrand();
}



