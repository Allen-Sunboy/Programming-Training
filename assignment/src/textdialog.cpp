#include "textdialog.h"
#include "ui_textdialog.h"

textDialog::textDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::textDialog)
{
    ui->setupUi(this);
}

QString textDialog::getName()
{
    return ui->lineEditName->text();
}

QString textDialog::getContent()
{
    return ui->lineEditContent->text();
}

textDialog::~textDialog()
{
    delete ui;
}
