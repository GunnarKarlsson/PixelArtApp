#ifndef PIXELARTCANVAS_H
#define PIXELARTCANVAS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "palette.h"

class PixelArtCanvas : public QGraphicsView
{
    Q_OBJECT

public:
    PixelArtCanvas(QWidget *parent = 0);
    ~PixelArtCanvas();

public slots:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void render();
    int getWidth();
    int getHeight();
    void setPalette(Palette *palette);

private:
    int selectionIndex = 0;
    const int borderSize = 10;
    const int cellSize = 20;
    const int row_count = 16;
    const int col_count = 16;
    QGraphicsScene *scene;
    std::vector<QColor*> canvasColors;
    Palette *palette;
    bool isMousePressed = false;
    int lastMousePosX = 0;
    int lastMousePosY = 0;
};

#endif // PIXELARTCANVAS_H
