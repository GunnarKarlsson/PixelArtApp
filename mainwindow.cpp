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

    PixelImage *pixelImage = new PixelImage();
    for (int i = 0; i < (12 * 12); i++) { //TODO; remove hardcoded size
        QColor *c = new QColor();
        c->setNamedColor("#FFF1E8");
        pixelImage->canvasColors.push_back(c);
    }
    frames.push_back(pixelImage);

    imageSequence = new ImageSequence(frames);
    imageSequence->setFixedSize(imageSequence->getWidth(), imageSequence->getHeight());

    pixelArtCanvas = new PixelArtCanvas(frames);
    pixelArtCanvas->setPalette(palette);
    pixelArtCanvas->setImageSequence(imageSequence);
    pixelArtCanvas->setFixedSize(pixelArtCanvas->getWidth(), pixelArtCanvas->getHeight());

    saveButton = new QPushButton("SAVE");
    connect(saveButton, SIGNAL (released()),this, SLOT (save()));

    addFrameButton = new QPushButton("ADD FRAME");
    connect(addFrameButton, SIGNAL (released()),this, SLOT (addImage()));

    //saveButton->setFont(font);
    //QFont f = saveButton->font();
    //f.setPointSize(16);
    //saveButton->setFont(f);
    //saveButton->setStyleSheet("background-color: #FFFFFF;");

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QLayout *imageListLayout = new QHBoxLayout();
    imageListLayout->addWidget(addFrameButton);
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

void MainWindow::addImage() {
    imageSequence->addImage();
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
