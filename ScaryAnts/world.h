#ifndef WORLD_H
#define WORLD_H

#include <QWidget>

class Ant;

class World : public QWidget
{
    Q_OBJECT
public:
    explicit World(QWidget *parent = 0);

    void startGame();
    void stopGame();

    quint64 createAnt();

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

signals:

public slots:
private:
    void drawAnts(QPainter *painter);
    void drawAnt(QPainter *painter, Ant *ant);

    bool _gameStarted;
    QHash<quint64,Ant*> _antHash;
};

#endif // WORLD_H
