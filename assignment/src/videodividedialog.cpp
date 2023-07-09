#include "videodividedialog.h"
#include "ui_videodividedialog.h"

videoDivideDialog::videoDivideDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videoDivideDialog)
{
    ui->setupUi(this);

    ui->timeEdit->setMinimumTime(QTime(0, 0, 1));
}

videoDivideDialog::~videoDivideDialog()
{
    delete ui;
}

void videoDivideDialog::showDuration(int duration)
{
    QString str;
    str.setNum(duration);
    ui->labelDuration->setText(str);

    QTime time;
    time = time.addSecs(duration - 1);
    ui->timeEdit->setMaximumTime(time);
}

int videoDivideDialog::getTime()
{
    int dot = ui->timeEdit->time().hour() * 3600 + ui->timeEdit->time().minute() * 60 + ui->timeEdit->time().second();
    return dot;
}
