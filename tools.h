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
    static const int Pen = 0;
    static const int Eraser = 1;
    static const int Fill = 2;

public slots:
    void mouseReleaseEvent(QMouseEvent * e);
    void selectPen();
    void selectEraser();
    void selectFill();

private:
   void clearAllButtonSelections();
   QGraphicsScene *scene;
   int toolSize = 50;
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
