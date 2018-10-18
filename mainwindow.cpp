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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(840, 680);

    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/Font/Pixeled.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    fileName = getLastOpenedFileName();
    if (fileName.length() == 0) {
        fileName = "pixella_" + QString::number(QDateTime::currentSecsSinceEpoch());
        saveLastOpenedFileName();
    }
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

    tools = new Tools(&toolSelection);
    tools->setFixedSize(tools->getWidth(), tools->getHeight());

    imageSequence = new ImageSequence(&frames, &frameIndex);
    imageSequence->setFixedSize(imageSequence->getWidth(), imageSequence->getHeight());

    pixelArtCanvas = new PixelArtCanvas(&frames, &frameIndex, &toolSelection);
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

    addFrameButton = new QPushButton("+FRAME");
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
    canvasAndPaletteLayout->addWidget(tools);
    canvasAndPaletteLayout->addWidget(palette);

    mainLayout->addLayout(canvasAndPaletteLayout);

    QLayout *movieScreenLayout = new QHBoxLayout();
    movieScreenLayout->addWidget(imageSequence);
    movieScreenLayout ->addWidget(movieScreen);
    mainLayout->addLayout(movieScreenLayout);

    ui->centralWidget->setLayout(mainLayout);
}

void MainWindow::styleButton(QPushButton *button, QFont &font) {
    button->setFont(font);
    QFont f = button->font();
    f.setPointSize(12);
    button->setFont(f);
    button->setStyleSheet(" QPushButton { background-color: transparent; color: #FFFFFF;} QPushButton::pressed { background-color: transparent; color: #FF77A9; }");
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
    PixelImage * currentImage = frames[frameIndex];
    frames.push_back(new PixelImage(*currentImage));
    imageSequence->render(true);
}

void MainWindow::doExport() {
    //TODO: export all frames, not just one

    int offset = 0;
    QRect rect(pixelArtCanvas->x(), pixelArtCanvas->y() + offset, pixelArtCanvas->getWidth(), pixelArtCanvas->getHeight());

    QImage image = grab(rect).toImage();
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    QString filePath = "Pixella_image_" +   QString::number(time) + ".png";
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

    saveLastOpenedFileName();
}

void MainWindow::write(QJsonObject &json) {
    json["id"] = "id";
    json["frame_count"] = (int)frames.size();
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
    saveLastOpenedFileName();
}

void MainWindow::loadFile(QString filename) {

    QFile jsonFile(filename);
    jsonFile.open(QFile::ReadOnly);
    QString s = jsonFile.readAll();

    this->fileName = filename.mid(filename.lastIndexOf("/"));
    setWindowTitle("Pixella: [ " + fileName + " ]");
    saveLastOpenedFileName();

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

    frameIndex = 0;

    imageSequence->selectionIndex = 0;

    movieScreen->stop();
    movieScreen->frameIndex = 0;

    pixelArtCanvas->render(true);

    imageSequence->render(true);

}

void MainWindow::createNew() {
    fileName = "Pixella_ " + QString::number(QDateTime::currentSecsSinceEpoch());
    frameIndex = 0;
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

    pixelArtCanvas->render(true);
    pixelArtCanvas->setSceneRect(0-5, 0-5, pixelArtCanvas->width(), pixelArtCanvas->height());
    imageSequence->selectionIndex = 0;
    imageSequence->render(true);
    imageSequence->setSceneRect(0-5, 0-5, imageSequence->width(), imageSequence->height());

    movieScreen->stop();
    movieScreen->frameIndex = 0;

    movieScreen->render();
}

QString MainWindow::getLastOpenedFileName() {
    QFile file(lastOpenedReferenceFilename);

    file.open(QFile::ReadOnly);
    QString s = file.readAll();
    qDebug() << "opened file: " << s << endl;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(s.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QString name = jsonObject["previousFile"].toString();
    if (name == nullptr) {
        name = "";
    }
    return name;
}

void MainWindow::saveLastOpenedFileName() {
    QFile file(lastOpenedReferenceFilename);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Couldn't open last ref file." << endl;
        return;
    } else {
        qDebug() << "last ref file opened";
    }

    QJsonObject json;
    json["previousFile"] = fileName;

    QJsonDocument doc(json);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    qDebug() << "out last ref: " << strJson << endl;

    QTextStream stream( &file );
    stream << strJson << endl;
}
