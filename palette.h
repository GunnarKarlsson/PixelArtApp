#ifndef PALETTE_H
#define PALETTE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

class Palette : public QGraphicsView
{
    Q_OBJECT

public:
    Palette(QWidget *parent = 0);
    ~Palette();

public slots:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
private:
       QGraphicsScene * scene;
};

#endif // PALETTE_H
