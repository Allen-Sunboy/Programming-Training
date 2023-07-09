#include "imagesetdialog.h"
#include "ui_imagesetdialog.h"

#include <QTime>

imageSetDialog::imageSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageSetDialog)
{
    ui->setupUi(this);
    group = new QButtonGroup(this);
    group->addButton(ui->radioButtonNo, 0);
    group->addButton(ui->radioButtonFade, 1);
    group->addButton(ui->radioButtonTrans, 2);
    group->addButton(ui->radioButtonRotation, 3);


    ui->timeEditDuration->setMinimumTime(QTime(0, 0, 1));
}

imageSetDialog::~imageSetDialog()
{
    delete ui;
}

void imageSetDialog::showStartEnd(int start, int duration)
{
    QTime startTime(0, 0, start);
    QTime dur(0, 0, duration);
    ui->timeEditStart->setTime(startTime);
    ui->timeEditDuration->setTime(dur);
}

void imageSetDialog::showXY(int x, int y)
{
    ui->spinBoxX->setValue(x);
    ui->spinBoxY->setValue(y);
}

void imageSetDialog::showEffectId(int i)
{
    group->button(i)->setChecked(true);
}


int imageSetDialog::getX()
{
    return ui->spinBoxX->value();
}

int imageSetDialog::getY()
{
    return ui->spinBoxY->value();
}

int imageSetDialog::getStart()
{
    int start = ui->timeEditStart->time().hour() * 3600 + ui->timeEditStart->time().minute() * 60 + ui->timeEditStart->time().second();
    return start;
}

int imageSetDialog::getDuration()
{
    int duration = ui->timeEditDuration->time().hour() * 3600 + ui->timeEditDuration->time().minute() * 60 + ui->timeEditDuration->time().second();
    return duration;
}

int imageSetDialog::getEffectId()
{
    return group->checkedId();
}
