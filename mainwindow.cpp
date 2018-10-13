#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <common.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(400, 300);

    ui->setupUi(this);

    palette = new Palette();
    palette->setFixedSize(160, 160);

    QLayout * layout = new QHBoxLayout();
    ui->centralWidget->setLayout(layout);
    layout->addWidget(palette);
}


MainWindow::~MainWindow()
{
    delete ui;
}
