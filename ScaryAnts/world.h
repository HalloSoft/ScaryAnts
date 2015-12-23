#ifndef WORLD_H
#define WORLD_H

#include "ant.h"
#include <QWidget>


class World : public QWidget
{
    Q_OBJECT
public:
    explicit World(QWidget *parent = 0);

    void startGame();
    void stopGame();
    bool isGameRunning() const { return _gameStarted;}

    quint64 createAnt(const QPointF startPoint = QPointF(), Ant::AntType type = Ant::common);
    AntHash antHash() const { return _antHash;}

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

signals:

public slots:
private:
    static const int interval;
    void drawAnts(QPainter *painter);
    void drawAnt(QPainter *painter, Ant *ant);
    void drawInfo(QPainter *painter);

    float randomFactor() const;

    bool _gameStarted;
    AntHash _antHash;
    quint64 _livecycleCounter {0};
};

#endif // WORLD_H
