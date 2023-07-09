#include "instructdialog.h"
#include "ui_instructdialog.h"

instructDialog::instructDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instructDialog)
{
    ui->setupUi(this);
}

instructDialog::~instructDialog()
{
    delete ui;
}
