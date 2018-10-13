#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QDateTime>
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

    saveButton = new QPushButton("save");
    connect(saveButton, SIGNAL (released()),this, SLOT (save()));

    QLayout * layout = new QHBoxLayout();
    ui->centralWidget->setLayout(layout);
    layout->addWidget(saveButton);
    layout->addWidget(pixelArtCanvas);
    layout->addWidget(palette);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save() {
    qDebug() << "Save()" << endl;

    qDebug() << "pixelArtCanvas x: " << pixelArtCanvas->rect().x() << endl;

    int offset = 0;
    QRect rect(pixelArtCanvas->x(), pixelArtCanvas->y() + offset, pixelArtCanvas->getWidth(), pixelArtCanvas->getHeight());

    QImage image = grab(rect).toImage();
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    QString filePath = "/Users/gunnarkarlsson/nano_pixel_image_" +   QString::number(time) + ".png";
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        image.save(&file, "PNG");
        qDebug() << "File saved" << endl;
    }
    else {
        qDebug() << "Can't open file: ";
    }
}
