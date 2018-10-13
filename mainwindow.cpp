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

    palette = new Palette();
    palette->setFixedSize(palette->getWidth(), palette->getHeight());

    pixelArtCanvas = new PixelArtCanvas();
    pixelArtCanvas->setPalette(palette);
    pixelArtCanvas->setFixedSize(pixelArtCanvas->getWidth(), pixelArtCanvas->getHeight());

    QLayout * layout = new QHBoxLayout();
    ui->centralWidget->setLayout(layout);
    layout->addWidget(pixelArtCanvas);
    layout->addWidget(palette);
}


MainWindow::~MainWindow()
{
    delete ui;
}
