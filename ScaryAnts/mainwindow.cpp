#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->world->setPrivacyRadiusVisible(ui->checkBoxPrivacyRange->isChecked());
    ui->world->setInteractionRadiusVisible(ui->checkBoxViewRange->isChecked());

    _game = new Game(ui->world, this);

    bool isConnected = false;
    Q_UNUSED(isConnected);
    isConnected = connect(ui->buttonInit, SIGNAL(clicked()), this, SLOT(initGame()));   Q_ASSERT(isConnected);
    isConnected = connect(ui->buttonStart, SIGNAL(clicked()), this, SLOT(startGame())); Q_ASSERT(isConnected);

    isConnected = connect(ui->checkBoxViewRange,
                          SIGNAL(toggled(bool)),
                          ui->world,
                          SLOT(setInteractionRadiusVisible(bool)));
    Q_ASSERT(isConnected);

    isConnected = connect(ui->checkBoxPrivacyRange,
                          SIGNAL(toggled(bool)),
                          ui->world,
                          SLOT(setPrivacyRadiusVisible(bool)));
    Q_ASSERT(isConnected);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    _game->initialize();
}

void MainWindow::startGame()
{
    if(ui->world->isGameRunning())
    {
        _game->stop();
        ui->buttonStart->setText("Start");
    }
    else
    {
        _game->start();
        ui->buttonStart->setText("Stop");
    }
}
