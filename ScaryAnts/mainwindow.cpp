#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool isConnected = false;                                                           Q_UNUSED(isConnected);
    isConnected = connect(ui->buttonInit, SIGNAL(clicked()), this, SLOT(initGame()));   Q_ASSERT(isConnected);
    isConnected = connect(ui->buttonStart, SIGNAL(clicked()), this, SLOT(startGame())); Q_ASSERT(isConnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    ui->world->createAnt();
    ui->world->repaint();
}

void MainWindow::startGame()
{
    ui->world->startGame();
}
