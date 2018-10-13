#include "palette.h"
#include "common.h"

Palette::Palette(QWidget *parent) {

    scene = new QGraphicsScene();
    setScene(scene);
    setAlignment(Qt::AlignTop|Qt::AlignLeft);

    PaletteColor *c1 = new PaletteColor("#000000");
    paletteColors.push_back(c1);
    PaletteColor *c2 = new PaletteColor("#1D2B52");
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
    QColor color;
    color.setNamedColor("#999999");
    QBrush brush(color);
    scene->addRect(QRect(0,0,20,20), pen, brush);
}
