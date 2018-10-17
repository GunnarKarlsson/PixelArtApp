#ifndef TOOLS_H
#define TOOLS_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>
#include <QGraphicsView>

class Tools : public QGraphicsView
{
    Q_OBJECT

public:
    Tools(QWidget *parent  = 0);
    ~Tools();
    void render();
    int getWidth();
    int getHeight();
    int toolSelection = 0;

public slots:
    void mouseReleaseEvent(QMouseEvent * e);

private:
   QGraphicsScene *scene;
   int toolSize = 32;
   QGraphicsPixmapItem *penOffPixmapItem;
   QPixmap *iconOnPen;
   QPixmap *iconOffPen;
   QPixmap *iconOnEraser;
   QPixmap *iconOffEraser;
   QPixmap *iconOnFill;
   QPixmap *iconOffFill;
   QBrush *onBrush;
   QBrush *offBrush;
   QPen *noPen;
};

#endif // TOOLS_H
