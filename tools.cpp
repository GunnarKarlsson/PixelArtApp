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

    *toolSelection = Pen;

    penButton = new QPushButton();
    penButton->setFixedSize(50, 50);
    iconOffPen = new QPixmap(":/Icons/pen_32x32.png");
    iconOnPen = new QPixmap(":/Icons/pen_white_32x32.png");
    QIcon ButtonIcon1(*iconOnPen);
    penButton->setIcon(ButtonIcon1);
    penButton->setIconSize(iconOffPen->rect().size());
    penButton->setStyleSheet(" QPushButton { background-color: black;}");
    layout->addWidget(penButton);
    connect(penButton, SIGNAL(released()), this, SLOT(selectPen()));

    eraserButton = new QPushButton();
    eraserButton->setFixedSize(50, 50);
    iconOffEraser = new QPixmap(":/Icons/eraser_32x32.png");
    iconOnEraser = new QPixmap(":/Icons/eraser_white_32x32.png");
    QIcon ButtonIcon2(*iconOffEraser);
    eraserButton->setIcon(ButtonIcon2);
    eraserButton->setIconSize(iconOffEraser->rect().size());
    eraserButton->setStyleSheet(" QPushButton { background-color: transparent;}");
    layout->addWidget(eraserButton);
    connect(eraserButton, SIGNAL(released()), this, SLOT(selectEraser()));

    fillButton = new QPushButton();
    fillButton->setFixedSize(50, 50);
    iconOffFill = new QPixmap(":/Icons/fill_32x32.png");
    iconOnFill = new QPixmap(":/Icons/fill_white_32x32.png");
    QIcon ButtonIcon3(*iconOffFill);
    fillButton->setIcon(ButtonIcon3);
    fillButton->setIconSize(iconOffFill->rect().size());
    fillButton->setStyleSheet(" QPushButton { background-color: transparent;}");
    layout->addWidget(fillButton);
    connect(fillButton, SIGNAL(released()), this, SLOT(selectFill()));

    setLayout(layout);
}

Tools::~Tools() {

}

void Tools::render() {
    this->show();
}

int Tools::getWidth() {
    return 62;
}

int Tools::getHeight() {
   return 172;
}

bool Tools::eventFilter(QObject *obj, QEvent *e) {
     //qDebug() << "eventfilter" << e->MouseButtonPress<< endl;
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
    clearAllButtonSelections();
    QIcon buttonIcon(*iconOnPen);
    penButton->setStyleSheet(" QPushButton { background-color: black;}");
    penButton->setIcon(buttonIcon);
    penButton->setIconSize(iconOnPen->rect().size());

    *toolSelection = Pen;
}

void Tools::selectEraser() {
    qDebug() << "selectEraser()" << endl;
    clearAllButtonSelections();
    QIcon buttonIcon(*iconOnEraser);
    eraserButton->setStyleSheet(" QPushButton { background-color: black;}");
    eraserButton->setIcon(buttonIcon);
    eraserButton->setIconSize(iconOnEraser->rect().size());

    *toolSelection = Eraser;
}

void Tools::selectFill() {
    qDebug() << "selectFill()" << endl;
    clearAllButtonSelections();
    QIcon buttonIcon(*iconOnFill);
    fillButton->setStyleSheet(" QPushButton { background-color: black;}");
    fillButton->setIcon(buttonIcon);
    fillButton->setIconSize(iconOnFill->rect().size());

    *toolSelection = Fill;
}

void Tools::clearAllButtonSelections() {
    QIcon buttonIconPen(*iconOffPen);
    penButton->setStyleSheet(" QPushButton { background-color: transparent;}");
    penButton->setIcon(buttonIconPen);

    QIcon buttonIconEraser(*iconOffEraser);
    eraserButton->setStyleSheet(" QPushButton { background-color: transparent;}");
    eraserButton->setIcon(buttonIconEraser);

    QIcon buttonIconFill(*iconOffFill);
    fillButton->setStyleSheet(" QPushButton { background-color: transparent;}");
    fillButton->setIcon(buttonIconFill);
}
