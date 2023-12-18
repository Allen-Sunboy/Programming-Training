#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setGeometry(50, 50, 100, 100);

    resize(800, 800);

    image[0] = ":/res/images/img1.png";
    image[1] = ":/res/images/img2.png";
    image[2] = ":/res/images/img3.png";
    image[3] = ":/res/images/img4.png";

    pixmap = new QPixmap(image[0]);

    now = 0;


    ui->pushButton->resize(pixmap->size());
    ui->pushButton->setIconSize(pixmap->size());
    ui->pushButton->setIcon(*pixmap);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeImage()
{
    if (now == 3)
    {
        now = 0;
    }
    else
    {
        now++;
    }
    pixmap->load(image[now]);
    ui->pushButton->resize(pixmap->size());
    ui->pushButton->setIconSize(pixmap->size());
    ui->pushButton->setIcon(*pixmap);
    return;

}

