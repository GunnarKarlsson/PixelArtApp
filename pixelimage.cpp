#include "pixelimage.h"
#include <QDebug>

PixelImage::PixelImage() {
    for (int i = 0; i < (col_count * row_count); i++) {
        QColor *c = new QColor();
        c->setNamedColor("#FFF1E8");
        canvasColors.push_back(c);
    }
}

PixelImage::PixelImage(const PixelImage &other) {

    std::vector<QColor*> colors;

    for (int i = 0; i < other.canvasColors.size(); i++) {
        colors.push_back(new QColor(other.canvasColors.at(i)->name()));
    }

    this->canvasColors.swap(colors);
}

PixelImage::~PixelImage() {

}

void PixelImage::update(QColor *color, int index) {
    canvasColors[index] = color;
}

void PixelImage::render(QGraphicsScene *scene, int xPos, int yPos, int cellSize) {

    QPen noPen(Qt::NoPen);
    for (int i = 0; i < canvasColors.size(); i++) {
        int x = i % col_count;
        int y = i / row_count;
        QColor *color = canvasColors[i];
        QBrush brush(*color);
        int pixelWidth = cellSize/col_count;
        int pixelHeight = cellSize/row_count;
        scene->addRect(QRect((x*pixelWidth) + xPos,(y*pixelHeight),pixelWidth,pixelHeight), noPen, brush);
    }
}
