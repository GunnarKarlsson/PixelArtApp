#ifndef PIXELIMAGE_H
#define PIXELIMAGE_H

#include <QGraphicsScene>

class PixelImage
{

public:
    PixelImage();
    PixelImage(const PixelImage &other);
    ~PixelImage();
    void update(QColor *color, int index);
    void render(QGraphicsScene *, int x, int y, int cellSize);
    std::vector<QColor*> canvasColors;
    int row_count = 12;
    int col_count = 12;
};

#endif // PIXELIMAGE_H
