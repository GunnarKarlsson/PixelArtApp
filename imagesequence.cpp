#include "imagesequence.h"
#include <QDebug>

ImageSequence::ImageSequence(std::vector<PixelImage*> &frames, QWidget *parent) : QGraphicsView(parent){

    scene = new QGraphicsScene();
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignLeft);
    //setStyleSheet("background: transparent; border: transparent;");

    images = frames;

    //images.resize(0);
    //images.push_back(new PixelImage());
    qDebug() << "images.size() in ctor" << images.size() << endl;
    render(true);
}

ImageSequence::~ImageSequence() {

}

void ImageSequence::mousePressEvent(QMouseEvent * e) {
    qDebug() << "imageseq mousePressEvent" << endl;
     int x = e->pos().x();
     selectionIndex = x / cellSize;
     qDebug() << "selectionIndex: " << selectionIndex << endl;
}

void ImageSequence::mouseReleaseEvent(QMouseEvent * e) {}

void ImageSequence::mouseDoubleClickEvent(QMouseEvent * e) {}

void ImageSequence::mouseMoveEvent(QMouseEvent * e) {}

void ImageSequence::update(QColor *color, int selectionIndex) {
    render(true);
}

void ImageSequence::render(bool all) {
    qDebug() << "render images.size(): " << images.size() << endl;
    for (int i = 0; i < images.size(); i++) {
        PixelImage *p = images[i];
        p->render(scene, i * cellSize, 0, cellSize);
    }
}

int ImageSequence::getWidth() {
    return maxLength * cellSize;
}

int ImageSequence::getHeight() {
    return cellSize;
}

void ImageSequence::addImage() {
     images.push_back(new PixelImage());
     render(true);
}
