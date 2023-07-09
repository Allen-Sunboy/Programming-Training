#include "mediawidget.h"
#include "ui_mediawidget.h"

mediawidget::mediawidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mediawidget)
{
    ui->setupUi(this);
}

mediawidget::~mediawidget()
{
    delete ui;
}
