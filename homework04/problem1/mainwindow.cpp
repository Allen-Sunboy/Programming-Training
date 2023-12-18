#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(270, 300);

    m = new QSignalMapper(this);

    ui->pushButton_1->setGeometry(70, 110, 40, 30);
    ui->pushButton_2->setGeometry(115, 110, 40, 30);
    ui->pushButton_3->setGeometry(160, 110, 40, 30);
    ui->pushButton_4->setGeometry(70, 145, 40, 30);
    ui->pushButton_5->setGeometry(115, 145, 40, 30);
    ui->pushButton_6->setGeometry(160, 145, 40, 30);
    ui->pushButton_7->setGeometry(70, 180, 40, 30);
    ui->pushButton_8->setGeometry(115, 180, 40, 30);
    ui->pushButton_9->setGeometry(160, 180, 40, 30);
    ui->pushButton_0->setGeometry(115, 215, 40, 30);

    ui->pushButton_clear->setGeometry(160, 215, 40, 30);

    ui->textBrowser->setGeometry(70, 20, 130, 80);
    ui->textBrowser->setText(str);

    connect(ui->pushButton_1, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_2, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_3, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_4, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_5, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_6, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_7, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_8, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_9, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_0, SIGNAL(clicked()), m, SLOT(map()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), m, SLOT(map()));

    m->setMapping(ui->pushButton_1, 1);
    m->setMapping(ui->pushButton_2, 2);
    m->setMapping(ui->pushButton_3, 3);
    m->setMapping(ui->pushButton_4, 4);
    m->setMapping(ui->pushButton_5, 5);
    m->setMapping(ui->pushButton_6, 6);
    m->setMapping(ui->pushButton_7, 7);
    m->setMapping(ui->pushButton_8, 8);
    m->setMapping(ui->pushButton_9, 9);
    m->setMapping(ui->pushButton_0, 0);
    m->setMapping(ui->pushButton_clear, -1);

    connect(m, SIGNAL(mappedInt(int)), this, SLOT(AddNum(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddNum(int i)
{
    if (i == -1)
    {
        str.clear();
    }
    else
    {
        str.append((char)(i+'0'));
    }
    ui->textBrowser->setText(str);
}

