#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(500, 500);

    ui->textEdit_1->setGeometry(20, 100, 200, 200);
    ui->textEdit_2->setGeometry(270, 100, 200, 200);

    ui->textEdit_1->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->textEdit_1 && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = (QKeyEvent*)event;
        if(ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return )
        {
            QString str = ui->textEdit_1->toPlainText();
            ui->textEdit_2->append(str);

            ui->textEdit_1->clear();
            return true;
        }

    }
    return false;

}

