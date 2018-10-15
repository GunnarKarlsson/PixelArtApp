#include "palette.h"
#include "common.h"
#include <QDebug>

Palette::Palette(QWidget *parent) {

    scene = new QGraphicsScene();
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background: transparent; border: transparent;");

    noPen = new QPen(Qt::NoPen);
    noBrush = new QBrush(Qt::NoBrush);

    selectionPen = new QPen("#FFF0EA");
    selectionPen->setWidth(5);
    selectionPen->setCapStyle(Qt::SquareCap);
    selectionPen->setJoinStyle(Qt::MiterJoin);

    borderPen = new QPen("#000000");
    borderPen->setWidth(10);
    borderPen->setCapStyle(Qt::SquareCap);
    borderPen->setJoinStyle(Qt::MiterJoin);

    std::vector<QString> colors =
    {"#000000","#1D2B52","#7E2553","#008651",
     "#AB5135","#5F564F","#C2C3C7","#FFF1E8",
     "#FE044F","#FFA300","#FFEC26","#00E435",
     "#2AADFF","#82769C","#FF77A9","#FECCA9"
    };

    for (int i = 0; i < colors.size(); i++) {
        QColor *c = new QColor();
        c->setNamedColor(colors[i]);
        paletteColors.push_back(c);
    }
    render();
}

Palette::~Palette() {
    //TODO: delete paletteColors;
    delete noPen;
    delete borderPen;
    delete selectionPen;
    delete noBrush;
}

QColor Palette::getSelectedColor() {
    if (selectionIndex > col_count * row_count) {
        selectionIndex = 0;
    }
        return *(paletteColors[selectionIndex]);

}

int Palette::getWidth() {
    return row_count * cellSize + borderSize*2;
}

int Palette::getHeight() {
    return col_count * cellSize + borderSize*2;
}

void Palette::mousePressEvent(QMouseEvent * e) {
    int offset = 5;
    qDebug() << e->pos().x() << endl;
    qDebug() << e->pos().y() << endl;

    int x = e->pos().x();// - borderSize*2;
    x /= cellSize;
    x %= col_count;

    int y = e->pos().y();// - borderSize*2; //- offset;
    y /= cellSize;

    qDebug() << "x: "  << x << endl;
    qDebug() << "y: " << y << endl;

    selectionIndex = x + y * col_count;
    qDebug() << "selectionIndex: " << selectionIndex << endl;

    render();
    update();
}

void Palette::mouseReleaseEvent(QMouseEvent * e) {

}

void Palette::mouseDoubleClickEvent(QMouseEvent * e) {

}

void Palette::mouseMoveEvent(QMouseEvent * e) {

}

void Palette::render() {

    scene->clear();

    qDebug() << "border: "<< borderSize << endl;

    for (int i = 0; i < paletteColors.size(); i++) {
        int x = i % col_count;
        int y = i / row_count;
        QColor *color = paletteColors[i];
        QBrush brush(*color);
        scene->addRect(QRect((x*cellSize) + borderSize/2,(y*cellSize) + borderSize/2,cellSize,cellSize), *noPen, brush);
    }

    int selectionX = selectionIndex % col_count;
    int selectionY = selectionIndex / row_count;

    scene->addRect(QRect(0.0, 0.0, cellSize*col_count + borderSize, cellSize*row_count + borderSize), *borderPen, *noBrush);
    scene->addRect(QRect((selectionX*cellSize) + borderSize/2, (selectionY*cellSize) + borderSize/2, cellSize, cellSize), *selectionPen, *noBrush);
}
