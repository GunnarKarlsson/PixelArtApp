#ifndef IMAGESEQUENCE_H
#define IMAGESEQUENCE_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "pixelimage.h"

class ImageSequence : public QGraphicsView
{
    Q_OBJECT

public:
    ImageSequence(std::vector<PixelImage*> &frames, QWidget *parent = 0);
    ~ImageSequence();
    void update(QColor *color, int selectionIndex);
    void render(bool all);
    int getWidth();
    int getHeight();
    void addImage();

public slots:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

private:
    int selectionIndex = 0;
    const int borderSize = 10;
    const int cellSize = 60;
    int maxLength = 8;
    QGraphicsScene *scene;
    std::vector<PixelImage*> images;
};

#endif // IMAGESEQUENCE_H
