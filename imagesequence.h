#ifndef IMAGESEQUENCE_H
#define IMAGESEQUENCE_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include "pixelimage.h"
#include "pixelartcanvas.h"

class PixelArtCanvas;

class ImageSequence : public QGraphicsView
{
    Q_OBJECT

public:
    ImageSequence(std::vector<PixelImage*> *frames, int *frameIndex, QWidget *parent = 0);
    ~ImageSequence();
    void update(QColor *color, int selectionIndex);
    void render(bool all);
    int getWidth();
    int getHeight();
    void addImage();
    void setPixelArtCanvas(PixelArtCanvas *pac);
    int selectionIndex = 0;

public slots:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

private:

    const int borderSize = 10;
    const int cellSize = 60;
    int maxLength = 8;
    QGraphicsScene *scene;
    std::vector<PixelImage*> *images;
    int *frameIndex;
    PixelArtCanvas *pac;
    QPen *selectionPen;
    QBrush *noBrush;
};

#endif // IMAGESEQUENCE_H
