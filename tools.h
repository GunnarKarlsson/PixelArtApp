#ifndef TOOLS_H
#define TOOLS_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QPushButton>

class Tools : public QGraphicsView
{
    Q_OBJECT

public:
    Tools(int *toolSelection, QWidget *parent  = 0);
    ~Tools();
    void render();
    int getWidth();
    int getHeight();
    bool eventFilter(QObject *, QEvent*);

public slots:
    void mouseReleaseEvent(QMouseEvent * e);
    void selectPen();
    void selectEraser();
    void selectFill();

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
   QPushButton *penButton;
   QPushButton  *eraserButton;
   QPushButton *fillButton;
   int * toolSelection;
};

#endif // TOOLS_H
