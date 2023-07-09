#include "textdurationdialog.h"
#include "ui_textdurationdialog.h"

textDurationDialog::textDurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::textDurationDialog)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(1);
}

textDurationDialog::~textDurationDialog()
{
    delete ui;
}

int textDurationDialog::getDuration()
{
    return ui->spinBox->value();
}

void textDurationDialog::showDuration(int i)
{
    ui->spinBox->setValue(i);

}
