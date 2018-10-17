#include "tools.h"
#include <QDebug>
#include <QGraphicsPixmapItem>

Tools::Tools(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene();
    QPixmap penToolIcon(":/Icons/pen_32x32");
    QGraphicsPixmapItem* item = scene->addPixmap(penToolIcon);
    item->setPos(0, 0);
}

Tools::~Tools() {

}

void Tools::render() {

}

int Tools::getWidth() {
    toolSize;
}

int Tools::getHeight() {
    toolSize * 3;
}

void Tools::mouseReleaseEvent(QMouseEvent * e) {

}

