#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    QBrush brush1(Qt::red);
    QBrush brush2(Qt::blue);
    QBrush brush3(Qt::yellow);
    QPen pen1(Qt::yellow);

    pen1.setWidth(0);
    scene->addRect(QRect(-20,-20,20,20), pen1, brush1);
    scene->addRect(QRect(-20, 0, 20, 20), pen1, brush3);
    scene->addRect(QRect(0,0,20,20), pen1, brush1);
    scene->addRect(QRect(20,20,20,20), pen1, brush2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
