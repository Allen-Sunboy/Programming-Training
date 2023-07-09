#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(400, 300);

    tc = new TempConverter(0, this);

    ui->groupBoxC->setGeometry(0, 10, 200, 290);
    ui->groupBoxF->setGeometry(200, 10, 200, 290);

    ui->dialC->setGeometry(0, 20, 200, 200);
    ui->dialC->setRange(-100, 100);
    ui->dialF->setGeometry(0, 20, 200, 200);
    ui->dialF->setRange(-150, 250);

    ui->lcdNumberC->setGeometry(20, 220, 160, 50);
    ui->lcdNumberF->setGeometry(20, 220, 160, 50);

    connect(ui->dialC, SIGNAL(valueChanged(int)), tc, SLOT(setTempC(int)));
    connect(ui->dialC, SIGNAL(valueChanged(int)), ui->lcdNumberC, SLOT(display(int)));
    connect(tc, SIGNAL(tempCChanged(int)), ui->dialC, SLOT(setValue(int)));

    connect(ui->dialF, SIGNAL(valueChanged(int)), tc, SLOT(setTempF(int)));
    connect(ui->dialF, SIGNAL(valueChanged(int)), ui->lcdNumberF, SLOT(display(int)));
    connect(tc, SIGNAL(tempFChanged(int)), ui->dialF, SLOT(setValue(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

