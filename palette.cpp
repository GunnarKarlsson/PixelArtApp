#include "palette.h"
#include "common.h"
#include <QDebug>

Palette::Palette(QWidget *parent) {

    scene = new QGraphicsScene();
    setScene(scene);
    setAlignment(Qt::AlignTop|Qt::AlignLeft);

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

}

void Palette::mousePressEvent(QMouseEvent * e) {

}

void Palette::mouseReleaseEvent(QMouseEvent * e) {

}

void Palette::mouseDoubleClickEvent(QMouseEvent * e) {

}

void Palette::mouseMoveEvent(QMouseEvent * e) {

}

void Palette::render() {
    int size = 40;
    QPen pen(Qt::NoPen);

    for (int i = 0; i < paletteColors.size(); i++) {
        int x = i%4;
        int y = i/4;
        QColor *color = paletteColors[i];
        qDebug() << "color: " << color->name() << endl;
        QBrush brush(*color);
        scene->addRect(QRect(x*size,y*size,size,size), pen, brush);
    }
}
