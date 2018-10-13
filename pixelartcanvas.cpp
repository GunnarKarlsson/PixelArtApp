#include "pixelartcanvas.h"

PixelArtCanvas::PixelArtCanvas(QWidget *parent) {
    scene = new QGraphicsScene();
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setStyleSheet("background: transparent; border: transparent;");

    for (int i = 0; i < (col_count * row_count); i++) {
        QColor *c = new QColor();
        c->setNamedColor("#FFEC26");
        canvasColors.push_back(c);
    }
    render();
}

int PixelArtCanvas::getWidth() {
    return row_count * cellSize + borderSize*2;
}

int PixelArtCanvas::getHeight() {
    return col_count * cellSize + borderSize*2;
}

PixelArtCanvas::~PixelArtCanvas() {

}

void PixelArtCanvas::mousePressEvent(QMouseEvent * e) {

}

void PixelArtCanvas::mouseReleaseEvent(QMouseEvent * e) {

}

void PixelArtCanvas::mouseDoubleClickEvent(QMouseEvent * e) {

}

void PixelArtCanvas::mouseMoveEvent(QMouseEvent * e) {

}

void PixelArtCanvas::render() {

    QPen noPen(Qt::NoPen);
    QBrush noBrush(Qt::NoBrush);

    for (int i = 0; i < canvasColors.size(); i++) {
        int x = i % col_count;
        int y = i / row_count;
        QColor *color = canvasColors[i];
        QBrush brush(*color);
        scene->addRect(QRect((x*cellSize) + borderSize/2,(y*cellSize) + borderSize/2,cellSize,cellSize), noPen, brush);
    }
}
