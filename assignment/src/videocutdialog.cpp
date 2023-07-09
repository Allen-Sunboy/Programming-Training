#include "videocutdialog.h"
#include "ui_videocutdialog.h"

videoCutDialog::videoCutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videoCutDialog)
{
    ui->setupUi(this);
    ui->timeEditDuration->setMinimumTime(QTime(0, 0, 1));
}

videoCutDialog::~videoCutDialog()
{
    delete ui;
}

int videoCutDialog::getNewStart()
{
    int start = ui->timeEditStart->time().hour() * 3600 + ui->timeEditStart->time().minute() * 60 + ui->timeEditStart->time().second();
    return start;
}

int videoCutDialog::getNewDuration()
{
    int duration = ui->timeEditDuration->time().hour() * 3600 + ui->timeEditDuration->time().minute() * 60 + ui->timeEditDuration->time().second();
    return duration;
}

void videoCutDialog::showDuration(int duration)
{
    QString str;
    str.setNum(duration);
    ui->labelDuration->setText(QString(str));

}
