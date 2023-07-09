#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(500, 500);

    dlg = new Dialog(this);
    connect(ui->setdate, SIGNAL(triggered()), dlg, SLOT(exec()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

