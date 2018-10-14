#ifndef MOVIESCREEN_H
#define MOVIESCREEN_H

#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "pixelimage.h"

class MovieScreen : public QGraphicsView
{
    Q_OBJECT

public:
    MovieScreen(std::vector<PixelImage*> *frames, QWidget *parent = 0);
    ~MovieScreen();
    void play();
    void stop();
    void render();
    int getWidth();
    int getHeight();

public slots:
    void doUpdate();


private:
    void nextFrame();
    std::vector<PixelImage*> *frames;
    QTimer *timer;
    int frameTimeMs = 1000;
    QGraphicsScene *scene;
    int frameIndex = 0;
    int cellSize = 200;
};

#endif // MOVIESCREEN_H
