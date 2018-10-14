#include "imagesequence.h"

ImageSequence::ImageSequence(QWidget *parent) : QGraphicsView(parent){

    scene = new QGraphicsScene();
    setScene(scene); setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setStyleSheet("background: transparent; border: transparent;");

    images.push_back(new PixelImage());
    images.push_back((new PixelImage));
}

ImageSequence::~ImageSequence() {

}

void ImageSequence::mousePressEvent(QMouseEvent * e) {

}

void ImageSequence::mouseReleaseEvent(QMouseEvent * e) {

}

void ImageSequence::mouseDoubleClickEvent(QMouseEvent * e) {

}

void ImageSequence::mouseMoveEvent(QMouseEvent * e) {

}

void ImageSequence::render(bool all) {

    for (int i = 0; i < images.size(); i++) {
        PixelImage *p = images[i];
        p->render(scene, i * cellSize, 0, cellSize);
    }

}

int ImageSequence::getWidth() {
    return images.size() * cellSize;
}

int ImageSequence::getHeight() {
    return cellSize;
}
