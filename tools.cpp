#include "tools.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

Tools::Tools(int *tool, QWidget *parent) : QGraphicsView(parent) {
    toolSelection = tool;
    installEventFilter(this);
    QVBoxLayout *layout = new QVBoxLayout();

    scene = new QGraphicsScene(this);

    penButton = new QPushButton();
    QPixmap pixmap1(":/Icons/pen_32x32.png");
    QIcon ButtonIcon1(pixmap1);
    penButton->setIcon(ButtonIcon1);
    penButton->setIconSize(pixmap1.rect().size());
    layout->addWidget(penButton);
    connect(penButton, SIGNAL(released()), this, SLOT(selectPen()));


    eraserButton = new QPushButton();
    QPixmap pixmap2(":/Icons/eraser_32x32.png");
    QIcon ButtonIcon2(pixmap2);
    eraserButton->setIcon(ButtonIcon2);
    eraserButton->setIconSize(pixmap2.rect().size());
    layout->addWidget(eraserButton);
    connect(eraserButton, SIGNAL(released()), this, SLOT(selectEraser()));

    fillButton = new QPushButton();
    QPixmap pixmap3(":/Icons/fill_32x32.png");
    QIcon ButtonIcon3(pixmap3);
    fillButton->setIcon(ButtonIcon3);
    fillButton->setIconSize(pixmap3.rect().size());
    layout->addWidget(fillButton);
    connect(fillButton, SIGNAL(released()), this, SLOT(selectFill()));

    setLayout(layout);

    //view->show();
}

Tools::~Tools() {

}

void Tools::render() {
    this->show();
}

int Tools::getWidth() {
    return 60;
}

int Tools::getHeight() {
   return 180;
}

bool Tools::eventFilter(QObject *obj, QEvent *e) {
     qDebug() << "eventfilter" << e->MouseButtonPress<< endl;
    return true;
}

void Tools::mouseReleaseEvent(QMouseEvent * e) {
    qDebug() << e->pos().y() << endl;

    int selection = e->pos().y() / 60;
    if (selection < 0) {
        selection = 0;
    }
    if (selection > 2) {
        selection = 2;
    }
    *toolSelection = selection;
}

void Tools::selectPen() {
    qDebug() << "selectPen()" << endl;
}

void Tools::selectEraser() {
    qDebug() << "selectEraser()" << endl;
}

void Tools::selectFill() {
    qDebug() << "selectFill()" << endl;
}
