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
#include <QFileDialog>
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

    fileName = "frames_save.json";
    setWindowTitle("Pixella: [ " + fileName + " ]");

    QFile jsonFile(fileName);
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

    newFileButton = new QPushButton("NEW");
    styleButton(newFileButton, font);
    connect(newFileButton, SIGNAL(released()), this, SLOT(createNew()));

    openButton = new QPushButton("OPEN");
    styleButton(openButton, font);
    connect(openButton, SIGNAL(released()), this, SLOT(openFile()));

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


    QLayout *buttonBarLayout = new QHBoxLayout();
    buttonBarLayout->addWidget(newFileButton);
    buttonBarLayout->addWidget(openButton);
    buttonBarLayout->addWidget(addFrameButton);
    buttonBarLayout->addWidget(playButton);
    buttonBarLayout->addWidget(stopButton);
    buttonBarLayout->addWidget(saveButton);
    buttonBarLayout->addWidget(exportButton);
    mainLayout->addLayout(buttonBarLayout);


    QLayout * canvasAndPaletteLayout = new QHBoxLayout();
    canvasAndPaletteLayout->addWidget(pixelArtCanvas);
    canvasAndPaletteLayout->addWidget(palette);
    mainLayout->addLayout(canvasAndPaletteLayout);

    QLayout *imageSequenceLayout = new QHBoxLayout();
    imageSequenceLayout->addWidget(imageSequence);
    mainLayout->addLayout(imageSequenceLayout);

    QLayout *movieScreenLayout = new QHBoxLayout();
    movieScreenLayout ->addWidget(movieScreen);
    mainLayout->addLayout(movieScreenLayout);

    ui->centralWidget->setLayout(mainLayout);
}

void MainWindow::styleButton(QPushButton *button, QFont &font) {
    button->setFont(font);
    QFont f = button->font();
    f.setPointSize(12);
    button->setFont(f);
    button->setStyleSheet("background: transparent; color: #FFFFFF;");
}


MainWindow::~MainWindow()
{
    delete ui;
    delete pixelArtCanvas;
    delete palette;
    delete imageSequence;
    delete movieScreen;
    delete exportButton;
    delete addFrameButton;
    delete playButton;
    delete saveButton;
    //TODO: delete frames
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

    QFile file(this->fileName);

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

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this,
            tr("Open File"), "",
            tr("All Files (*)"));
    loadFile(filename);
}

void MainWindow::loadFile(QString filename) {

    QFile jsonFile(filename);
    jsonFile.open(QFile::ReadOnly);
    QString s = jsonFile.readAll();
    qDebug() << "opened file: " << s << endl;

    this->fileName = filename.mid(filename.lastIndexOf("/"));
    setWindowTitle("Pixella: [ " + fileName + " ]");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(s.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonFramesArray = jsonObject["frames"].toArray();
    qDebug() << "frames read from file: " << jsonFramesArray.size() << endl;

    if (jsonFramesArray.size() == 0) {
        qDebug() << "no frames loaded " << endl;
        return;
    }
    frames.clear();

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

    pixelArtCanvas->render(true);
    imageSequence->render(true);
}

void MainWindow::createNew() {
    fileName = "frames_save_ " + QString::number(QDateTime::currentSecsSinceEpoch());
    frames.clear();
    setWindowTitle("Pixella: [ " + fileName + " ]");
    //Add initial Data
    PixelImage *pixelImage = new PixelImage();
    for (int i = 0; i < (12 * 12); i++) { //TODO; remove hardcoded size
        QColor *c = new QColor();
        c->setNamedColor("#FFF1E8");
        pixelImage->canvasColors.push_back(c);
    }
    frames.push_back(pixelImage);
    frameIndex = 0;
    pixelArtCanvas->render(true);
    imageSequence->render(true);
    movieScreen->render();
}
