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
    bool isGameRunning() const { return _gameStarted;}

    quint64 createAnt(const QPointF startPoint = QPointF());
    QHash<quint64,Ant*> antHash() const { return _antHash;}

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

signals:

public slots:
private:
    static const int interval;
    void drawAnts(QPainter *painter);
    void drawAnt(QPainter *painter, Ant *ant);

    float randomFactor() const;

    bool _gameStarted;
    QHash<quint64,Ant*> _antHash;
};

#endif // WORLD_H
