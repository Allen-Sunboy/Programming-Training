#include "textsetdialog.h"
#include "ui_textsetdialog.h"


textSetDialog::textSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::textSetDialog)
{
    ui->setupUi(this);


    ui->timeEditDuration->setMinimumTime(QTime(0, 0, 1));
}

textSetDialog::~textSetDialog()
{
    delete ui;
}

void textSetDialog::showStartEnd(int start, int duration)
{
    QTime startTime(0, 0, start);
    QTime dur(0, 0, duration);
    ui->timeEditStart->setTime(startTime);
    ui->timeEditDuration->setTime(dur);

}

void textSetDialog::showXY(int x, int y)
{
    ui->spinBoxX->setValue(x);
    ui->spinBoxY->setValue(y);
}


int textSetDialog::getX()
{
    return ui->spinBoxX->value();
}

int textSetDialog::getY()
{
    return ui->spinBoxY->value();
}

int textSetDialog::getStart()
{
    int start = ui->timeEditStart->time().hour() * 3600 + ui->timeEditStart->time().minute() * 60 + ui->timeEditStart->time().second();
    return start;
}

int textSetDialog::getDuration()
{
    int duration = ui->timeEditDuration->time().hour() * 3600 + ui->timeEditDuration->time().minute() * 60 + ui->timeEditDuration->time().second();
    return duration;
}

