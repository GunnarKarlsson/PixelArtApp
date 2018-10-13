#include "palette.h"
#include "common.h"
#include <QDebug>

Palette::Palette(QWidget *parent) {

    scene = new QGraphicsScene();
    setScene(scene);
    setAlignment(Qt::AlignTop|Qt::AlignLeft);

    QColor *c1 = new QColor();
    c1->setNamedColor("#999999");
    paletteColors.push_back(c1);
    QColor *c2 = new QColor();
    c2->setNamedColor("#BBBBBB");
    paletteColors.push_back(c2);
    render();
}

Palette::~Palette() {

}

void Palette::mousePressEvent(QMouseEvent * e) {

}

void Palette::mouseReleaseEvent(QMouseEvent * e) {

}

void Palette::mouseDoubleClickEvent(QMouseEvent * e) {

}

void Palette::mouseMoveEvent(QMouseEvent * e) {

}

void Palette::render() {
    QPen pen(Qt::NoPen);

    for (int i = 0; i < paletteColors.size(); i++) {
        QColor *color = paletteColors[i];
        qDebug() << "color: " << color->name() << endl;
        QBrush brush(*color);
        //brush.setColor(*color);
        scene->addRect(QRect(i*20,0,20,20), pen, brush);
    }
/*
    QColor color;
    color.setNamedColor("#999999");
    QBrush brush(color);
    scene->addRect(QRect(0,0,20,20), pen, brush);
*/
}
