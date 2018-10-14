#ifndef IMAGESEQUENCE_H
#define IMAGESEQUENCE_H

#include <QGraphicsView>
#include "pixelimage.h"

class ImageSequence : public QGraphicsView
{
    Q_OBJECT

public:
    ImageSequence(QWidget *parent = 0);
    ~ImageSequence();
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void render(bool all);
    int getWidth();
    int getHeight();
private:
    int selectionIndex = 0;
    const int borderSize = 10;
    const int cellSize = 24;
    int maxLength = 12;
    QGraphicsScene *scene;
    std::vector<PixelImage*> images;
};

#endif // IMAGESEQUENCE_H
