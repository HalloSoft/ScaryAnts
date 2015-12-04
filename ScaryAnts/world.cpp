#include "world.h"

#include "ant.h"

#include <QDebug>
#include <QPainter>
#include <QTime>

World::World(QWidget *parent) :
    QWidget(parent),
    _gameStarted(false)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec() * 1000);
    startTimer(500);

}

void World::startGame()
{
   _gameStarted = true;
}

void World::stopGame()
{
   _gameStarted = false;
}

quint64 World::createAnt()
{
    QList<quint64> idList =_antHash.keys();
    quint64 newId = 0;

    if(!idList.isEmpty())
    {
        qSort(idList);
        quint64 maxId = idList.last();

        newId = maxId + 1;
    }

    Ant *newAnt = new Ant;
    newAnt->setSpeed(QPointF(1, -1));

    _antHash.insert(newId, newAnt);

    return newId;
}

void World::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.eraseRect(rect());

    painter.fillRect(rect(), Qt::white);

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
        ant->processNewPosition();
        drawAnt(painter, ant);
    }
}

void World::drawAnt(QPainter *painter, Ant *ant)
{
    painter->setBrush(Qt::cyan);
    painter->setPen(Qt::darkCyan);
    QPointF position = ant->position() + QPointF(50, 50);
    painter->drawEllipse(position, 5, 5);

    //qDebug() << "Draw ant at" << position;
    qDebug() << "Rand:" << qrand();
}

