#include "imagesequence.h"
#include <QDebug>

ImageSequence::ImageSequence(std::vector<PixelImage*> *frames, int *frameIndex, QWidget *parent) : QGraphicsView(parent){
    scene = new QGraphicsScene();
    setScene(scene);
    setSceneRect(scene->sceneRect());
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignLeft);
    setStyleSheet("background: transparent; border: transparent;");

    selectionPen = new QPen("#000000");
    selectionPen->setWidth(4);
    selectionPen->setCapStyle(Qt::SquareCap);
    selectionPen->setJoinStyle(Qt::MiterJoin);

    noBrush = new QBrush(Qt::NoBrush);

    this->images = frames;
    this->frameIndex = frameIndex;

    render(true);
}

ImageSequence::~ImageSequence() {
    delete selectionPen;
    delete noBrush;
}

void ImageSequence::setPixelArtCanvas(PixelArtCanvas *pac) {
    this->pac = pac;
}

void ImageSequence::mousePressEvent(QMouseEvent * e) {
     int x = e->pos().x();
     selectionIndex = x / cellSize;
     *frameIndex = selectionIndex;
     if (pac) {
         pac->render(true);
     }
     render(true);

}

void ImageSequence::render(bool all) {
    if (all) {
        scene->clear();
        for (int i = 0; i < images->size(); i++) {
            PixelImage *p = images->at(i);
            p->render(scene, i * cellSize, 0, cellSize);
        }
        scene->addRect(QRect((selectionIndex * cellSize)-2, -2, cellSize+4, cellSize+4), *selectionPen, *noBrush);
    } else {
        PixelImage *p = images->at(selectionIndex);
        p->render(scene, (selectionIndex * cellSize), 0, cellSize);
        scene->addRect(QRect((selectionIndex * cellSize)-2, -2, cellSize+4, cellSize+4), *selectionPen, *noBrush);
    }
}

int ImageSequence::getWidth() {
    return maxLength * cellSize;
}

int ImageSequence::getHeight() {
    return cellSize + 4*2;
}

void ImageSequence::addImage() {
     images->push_back(new PixelImage());
     render(true);
}
