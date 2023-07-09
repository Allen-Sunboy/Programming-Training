#include "imagedurationdialog.h"
#include "ui_imagedurationdialog.h"

imageDurationDialog::imageDurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageDurationDialog)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(1);
}

imageDurationDialog::~imageDurationDialog()
{
    delete ui;
}

int imageDurationDialog::getDuration()
{
    return ui->spinBox->value();
}

void imageDurationDialog::showDuration(int i)
{
    ui->spinBox->setValue(i);
}
