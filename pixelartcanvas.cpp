#include "pixelartcanvas.h"
#include <QDebug>

PixelArtCanvas::PixelArtCanvas(std::vector<PixelImage*>  *frames, int *frameIndex, QWidget *parent) {
    this->frames = frames;
    this->frameIndex = frameIndex;
    scene = new QGraphicsScene();
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background: transparent; border: transparent;");
    render(true);
}

void PixelArtCanvas::setPalette(Palette *p) {
    palette = p;
}

void PixelArtCanvas::setImageSequence(ImageSequence *sequence) {
    imageSequence = sequence;
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
    int yOffset = 10;
    int xOffset = 10;
    //qDebug() << e->pos().x() << endl;
    //qDebug() << e->pos().y() << endl;

    int x = e->pos().x() - xOffset;
    x /= cellSize;
    x %= col_count;

    int y = e->pos().y() - yOffset;
    y /= cellSize;

    //qDebug() << "x: "  << x << endl;
    //qDebug() << "y: " << y << endl;

    int selectionIndex = x + y * col_count;
    //qDebug() << "selectionIndex: " << selectionIndex << endl;

    QColor selectedColor = palette->getSelectedColor();
    frames->at(*frameIndex)->canvasColors[selectionIndex]->setNamedColor(selectedColor.name());
    render(true);
    isMousePressed = true;
}

void PixelArtCanvas::mouseReleaseEvent(QMouseEvent * e) {
    isMousePressed = false;
}

void PixelArtCanvas::mouseDoubleClickEvent(QMouseEvent * e) {

}

void PixelArtCanvas::mouseMoveEvent(QMouseEvent * e) {
    if (!isMousePressed) {
        return;
    }
    int yOffset = 10;
    int xOffset = 10;

    int minMove = 5;

    int xChange = abs(lastMousePosX - e->pos().x());
    int yChange = abs(lastMousePosY - e->pos().y());

    if (xChange < minMove && yChange < minMove) {
        return;
    }

    //qDebug() << e->pos().x() << endl;
    //qDebug() << e->pos().y() << endl;

    lastMousePosX = e->pos().x();
    lastMousePosY = e->pos().y();

    int x = e->pos().x() - xOffset;
    x /= cellSize;
    x %= col_count;

    int y = e->pos().y() - yOffset;
    y /= cellSize;

    //qDebug() << "x: "  << x << endl;
    //qDebug() << "y: " << y << endl;

    selectionIndex = x + y * col_count;
    //qDebug() << "selectionIndex: " << selectionIndex << endl;

    QColor selectedColor = palette->getSelectedColor();
    if (selectionIndex > col_count * row_count) {
        selectionIndex = 0;
    }
    frames->at(*frameIndex)->canvasColors[selectionIndex]->setNamedColor(selectedColor.name());
    render(false);
}

void PixelArtCanvas::render(bool all) {

    QPen borderPen("#000000");
    borderPen.setWidth(10);
    borderPen.setCapStyle(Qt::SquareCap);
    borderPen.setJoinStyle(Qt::MiterJoin);

    QPen noPen(Qt::NoPen);
    QBrush noBrush(Qt::NoBrush);
    if (all) {
    for (int i = 0; i < frames->at(*frameIndex)->canvasColors.size(); i++) {
        int x = i % col_count;
        int y = i / row_count;
        QColor *color = frames->at(*frameIndex)->canvasColors[i];
        QBrush brush(*color);
        scene->addRect(QRect((x*cellSize) + borderSize/2,(y*cellSize) + borderSize/2,cellSize,cellSize), noPen, brush);
    }
    } else {
        int x = selectionIndex % col_count;
        int y = selectionIndex / row_count;
        QColor *color = frames->at(*frameIndex)->canvasColors[selectionIndex];
        QBrush brush(*color);
        scene->addRect(QRect((x*cellSize) + borderSize/2,(y*cellSize) + borderSize/2,cellSize,cellSize), noPen, brush);
        if (imageSequence) {
            qDebug() << "updating image seqeunce" << endl;
            imageSequence->update(color, selectionIndex);
        } else {
            qDebug() << "image sequence is null" << endl;
        }
    }
    scene->addRect(QRect(0.0, 0.0, cellSize*col_count + borderSize, cellSize*row_count + borderSize), borderPen, noBrush);
}
