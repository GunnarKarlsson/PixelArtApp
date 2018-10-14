#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QDateTime>
#include <QFontDatabase>
#include <common.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(680, 480);

    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/Font/Fipps-Regular.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    palette = new Palette();
    palette->setFixedSize(palette->getWidth(), palette->getHeight());

    pixelArtCanvas = new PixelArtCanvas();
    pixelArtCanvas->setPalette(palette);
    pixelArtCanvas->setFixedSize(pixelArtCanvas->getWidth(), pixelArtCanvas->getHeight());

    imageSequence = new ImageSequence();
    imageSequence->setFixedSize(imageSequence->getWidth(), imageSequence->getHeight());

    saveButton = new QPushButton("SAVE");
    saveButton->setFont(font);
    QFont f = saveButton->font();
    f.setPointSize(16);
    saveButton->setFont(f);
    saveButton->setStyleSheet("background-color: #FFFFFF;");
    connect(saveButton, SIGNAL (released()),this, SLOT (save()));

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QLayout *imageListLayout = new QHBoxLayout();
    imageListLayout->addWidget(new QPushButton("test1"));
    imageListLayout->addWidget(new QPushButton("test2"));
    imageListLayout->addWidget(new QPushButton("test3"));

    QLayout * layout = new QHBoxLayout();
    mainLayout->addLayout(layout);
    mainLayout->addWidget(imageSequence);
    mainLayout->addLayout(imageListLayout);
    ui->centralWidget->setLayout(mainLayout);
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
