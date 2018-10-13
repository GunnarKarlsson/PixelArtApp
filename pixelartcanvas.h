#ifndef PIXELARTCANVAS_H
#define PIXELARTCANVAS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

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
private:
       QGraphicsScene * scene;
};

#endif // PIXELARTCANVAS_H
