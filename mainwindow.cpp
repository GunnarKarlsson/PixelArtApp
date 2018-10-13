#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <common.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(680, 480);

    ui->setupUi(this);

    pixelArtCanvas = new PixelArtCanvas();
    pixelArtCanvas->setFixedSize(pixelArtCanvas->getWidth(), pixelArtCanvas->getHeight());

    palette = new Palette();
    palette->setFixedSize(palette->getWidth(), palette->getHeight());

    QLayout * layout = new QHBoxLayout();
    ui->centralWidget->setLayout(layout);
    layout->addWidget(pixelArtCanvas);
    layout->addWidget(palette);
}


MainWindow::~MainWindow()
{
    delete ui;
}
