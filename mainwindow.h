#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include "palette.h"
#include "pixelartcanvas.h"
#include "imagesequence.h"
#include "moviescreen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
     void save();
     void play();
     void stop();
     void addImage();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    PixelArtCanvas *pixelArtCanvas;
    Palette *palette;
    ImageSequence *imageSequence;
    MovieScreen *movieScreen;

    QPushButton *saveButton;
    QPushButton *addFrameButton;
    QPushButton *playButton;
    QPushButton *stopButton;
    std::vector<PixelImage*> frames;
    int frameIndex = 0;
};

#endif // MAINWINDOW_H
