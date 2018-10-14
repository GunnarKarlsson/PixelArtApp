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
    void render();
    int getWidth();
    int getHeight();
    QColor getSelectedColor();

public slots:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);


private:
    const int borderSize = 10;
    const int cellSize = 60;
    const int row_count = 4;
    const int col_count = 4;
    QGraphicsScene *scene;
    std::vector<QColor*> paletteColors;
    int selectionIndex = 0;
};

#endif // PALETTE_H
