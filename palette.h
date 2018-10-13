#ifndef PALETTE_H
#define PALETTE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "palettecolor.h"

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
    void render();
    int getWidth();
    int getHeight();
private:
       const int cellSize = 40;
       const int row_count = 4;
       const int col_count = 4;
       QGraphicsScene *scene;
       std::vector<QColor*> paletteColors;
       QColor *selectedColor;
};

#endif // PALETTE_H
