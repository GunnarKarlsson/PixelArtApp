#include "moviescreen.h"

MovieScreen::MovieScreen(std::vector<PixelImage*> *frames, QWidget *parent) : QGraphicsView(parent){
    scene = new QGraphicsScene();
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignLeft);
    this->frames = frames;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void MovieScreen::doUpdate() {
    nextFrame();
    render();
}

MovieScreen::~MovieScreen() {

}

void MovieScreen::play() {
    timer->start(frameTimeMs);
}

void MovieScreen::stop() {
    timer->stop();
}

void MovieScreen::render() {
    PixelImage *p = frames->at(frameIndex);
    p->render(scene, 0, 0, cellSize);
}

void MovieScreen::nextFrame() {
    frameIndex++;
    if (frameIndex > frames->size()) {
        frameIndex = 0;
    }
}

int MovieScreen::getWidth() {
    return cellSize;
}

int MovieScreen::getHeight() {
    return cellSize;
}
