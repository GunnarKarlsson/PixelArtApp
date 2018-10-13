#ifndef IMAGELIST_H
#define IMAGELIST_H


class ImageList : public QGraphicsView
{
    Q_OBJECT

public:
    ImageList(QWidget *parent = 0);
    ~ImageList();
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
    std::vector<QImage> canvasColors;
};

#endif // IMAGELIST_H
