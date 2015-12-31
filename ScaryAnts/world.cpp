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
    _interactionRadiusVisible(false),
    _privacyRadiusVisible(false),
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

quint64 World::createAnt(const QPointF startPoint, Ant::AntType type )
{
    QList<quint64> idList =_antHash.keys();
    quint64 newId = 0;

    if(!idList.isEmpty())
    {
        qSort(idList);
        quint64 maxId = idList.last();

        newId = maxId + 1;
    }

    Ant *newAnt = nullptr;
    if(type == Ant::common)
        newAnt = new CommonAnt(this);
    else
        newAnt = new SocialAnt(this);

    Q_CHECK_PTR(newAnt);

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

    drawInfo(&painter);
}

void World::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if(_gameStarted)
        repaint();
}

void World::setInteractionRadiusVisible(bool value)
{
    _interactionRadiusVisible = value;
    repaint();
}

void World::setPrivacyRadiusVisible(bool value)
{
    _privacyRadiusVisible = value;
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
    QBrush oldBrush = painter->brush();

    painter->setBrush(Qt::black);
    painter->setPen(QColor("brown"));

    QPointF startPointAnt = ant->position();
    float antRadius = ant->sizeRadus();
    painter->drawEllipse(startPointAnt, antRadius, antRadius);

    painter->setBrush(oldBrush);


    // draw interaction radius
    if(_interactionRadiusVisible)
    {
        const float radius = ant->interactionRadius();
        painter->setPen(Qt::green);
        painter->drawEllipse(startPointAnt, radius, radius);
    }

    // draw privacy radius
    if(_privacyRadiusVisible)
    {
        const float privacyRadius = ant->privacyRadius();
        painter->setPen(Qt::black);
        painter->drawEllipse(startPointAnt, privacyRadius, privacyRadius);
    }

    painter->setBrush(oldBrush);
}

void World::drawInfo(QPainter *painter)
{
    painter->drawText(10,15, QString::number(_livecycleCounter++));
}

