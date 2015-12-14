#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Game;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void initGame();
    void startGame();

private:
    static const quint32 antcount;

    Ui::MainWindow *ui;
    Game           *_game;
};

#endif // MAINWINDOW_H
