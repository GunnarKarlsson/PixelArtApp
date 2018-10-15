#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QDateTime>
#include <QFontDatabase>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <common.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(680, 680);

    ui->setupUi(this);

    //Load resources
    int id = QFontDatabase::addApplicationFont(":/Font/Pixeled.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    QString name = "frames_save.json";

    QFile jsonFile(name);
    jsonFile.open(QFile::ReadOnly);
    QString s = jsonFile.readAll();
    qDebug() << "opened file: " << s << endl;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(s.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonFramesArray = jsonObject["frames"].toArray();
    qDebug() << "frames read from file: " << jsonFramesArray.size() << endl;

    if (jsonFramesArray.size() == 0) {
        //Add initial Data
        PixelImage *pixelImage = new PixelImage();
        for (int i = 0; i < (12 * 12); i++) { //TODO; remove hardcoded size
            QColor *c = new QColor();
            c->setNamedColor("#FFF1E8");
            pixelImage->canvasColors.push_back(c);
        }
        frames.push_back(pixelImage);
    } else {
        for (int i = 0; i < jsonFramesArray.size(); i++) {
            QJsonObject jsonObj = jsonFramesArray[i].toObject();
            QJsonArray jsonColors = jsonObj["colors"].toArray();
            PixelImage *pixelImage = new PixelImage();
            pixelImage->canvasColors.clear();
            for (int i = 0; i < (12 * 12); i++) { //TODO; remove hardcoded size
                QColor *c = new QColor();
                qDebug() << jsonColors[i].toString() << endl;
                c->setNamedColor(jsonColors[i].toString());
                pixelImage->canvasColors.push_back(c);
            }
            frames.push_back(pixelImage);
        }
    }

    //add QGraphicViews
    palette = new Palette();
    palette->setFixedSize(palette->getWidth(), palette->getHeight());

    imageSequence = new ImageSequence(&frames, &frameIndex);
    imageSequence->setFixedSize(imageSequence->getWidth(), imageSequence->getHeight());

    pixelArtCanvas = new PixelArtCanvas(&frames, &frameIndex);
    pixelArtCanvas->setPalette(palette);
    pixelArtCanvas->setImageSequence(imageSequence);
    pixelArtCanvas->setFixedSize(pixelArtCanvas->getWidth(), pixelArtCanvas->getHeight());

    imageSequence->setPixelArtCanvas(pixelArtCanvas);

    movieScreen = new MovieScreen(&frames);
    movieScreen->setFixedSize(movieScreen->getWidth(), movieScreen->getHeight());

    //Add Buttons
    exportButton = new QPushButton("EXPORT");
    styleButton(exportButton, font);
    connect(exportButton, SIGNAL (released()),this, SLOT (doExport()));

    addFrameButton = new QPushButton("ADD FRAME");
    styleButton(addFrameButton, font);
    connect(addFrameButton, SIGNAL (released()),this, SLOT (addImage()));

    playButton = new QPushButton("PLAY");
    styleButton(playButton, font);
    connect(playButton, SIGNAL(released()), this, SLOT(play()));

    stopButton = new QPushButton("STOP");
    styleButton(stopButton, font);
    connect(stopButton, SIGNAL(released()), this, SLOT(stop()));

    saveButton = new QPushButton("SAVE");
    styleButton(saveButton, font);
    connect(saveButton, SIGNAL(released()), this, SLOT(save()));

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QLayout *actionBarLayout = new QHBoxLayout();
    actionBarLayout->addWidget(addFrameButton);
    actionBarLayout->addWidget(playButton);
    actionBarLayout->addWidget(stopButton);
    actionBarLayout->addWidget(saveButton);
    actionBarLayout->addWidget(exportButton);
    mainLayout->addLayout(actionBarLayout);

    QLayout *imageListLayout = new QHBoxLayout();
    imageListLayout->addWidget(movieScreen);

    QLayout * layout = new QHBoxLayout();
    mainLayout->addLayout(layout);
    mainLayout->addWidget(imageSequence);
    mainLayout->addLayout(imageListLayout);
    ui->centralWidget->setLayout(mainLayout);
    layout->addWidget(pixelArtCanvas);
    layout->addWidget(palette);
}

void MainWindow::styleButton(QPushButton *button, QFont &font) {
    button->setFont(font);
    QFont f = button->font();
    f.setPointSize(16);
    button->setFont(f);
    button->setStyleSheet("background: transparent; color: #FFFFFF;");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addImage() {
    //imageSequence->addImage();

    PixelImage * currentImage = frames[frameIndex];
    frames.push_back(new PixelImage(*currentImage));
    imageSequence->render(true);
}

void MainWindow::doExport() {
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

void MainWindow::play() {
    if (movieScreen) {
        movieScreen->play();
    }
}

void MainWindow::stop() {
    if (movieScreen) {
        movieScreen->stop();
    }
}

void MainWindow::save() {
    qDebug() << "save()" << endl;

    QString name = "frames_save.json";

    QFile file(name);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Couldn't open save file." << endl;
        return;
    } else {
        qDebug() << "file opened";
    }

    QJsonObject jsonObject;
    write(jsonObject);

    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    qDebug() << "out: " << strJson << endl;

    QTextStream stream( &file );
    stream << strJson << endl;
}

void MainWindow::write(QJsonObject &json) {
    json["id"] = "id";
    json["frame_count"] = (int)frames.size();
    json["created_date"] = "some_created_date";
    json["row_count"] = 12;
    json["row_count"] = 12;
    QJsonArray framesArray;
    for (int i = 0; i < frames.size(); i++) {
        QJsonObject jsonFrame;
        jsonFrame["index"] = i;
        QJsonArray jsonColors;
        for (int j = 0; j < frames[i]->canvasColors.size(); j++) {
            QColor *color = frames[i]->canvasColors[j];
            jsonColors.append(QJsonValue(color->name()));
        }
        jsonFrame["colors"] =  jsonColors;
        framesArray.append(jsonFrame);
    }
    json["frames"] =  framesArray;
}
