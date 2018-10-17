#include "tools.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QLabel>

Tools::Tools(QWidget *parent) : QGraphicsView(parent) {
    //scene = new QGraphicsScene();

    QVBoxLayout *layout = new QVBoxLayout();

    scene = new QGraphicsScene(this);
/*
    QGraphicsView* view = new QGraphicsView(scene, this); // Give the view a parent too to avoid memory leaks
    penOffPixmapItem = new QGraphicsPixmapItem(QPixmap(":/Icons/pen_32x32.png"));
*/


    QPixmap imagePen(":/Icons/pen_32x32.png");
    QLabel *imageLabelPen = new QLabel();
    imageLabelPen->setPixmap(imagePen);
    layout->addWidget(imageLabelPen);

    QPixmap imageEraser(":/Icons/eraser_32x32.png");
    QLabel *imageLabelEraser = new QLabel();
    imageLabelEraser->setPixmap(imageEraser);
    layout->addWidget(imageLabelEraser);

    QPixmap imageFill(":/Icons/fill_32x32.png");
    QLabel *imageLabelFill = new QLabel();
    imageLabelFill->setPixmap(imageFill);
    layout->addWidget(imageLabelFill);

    setLayout(layout);

    //view->show();
}

Tools::~Tools() {

}

void Tools::render() {
    this->show();
}

int Tools::getWidth() {
    32;
}

int Tools::getHeight() {
   32 * 3;
}

void Tools::mouseReleaseEvent(QMouseEvent * e) {

}

