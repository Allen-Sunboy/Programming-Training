#ifndef INSTRUCTDIALOG_H
#define INSTRUCTDIALOG_H

#include <QDialog>

namespace Ui {
class instructDialog;
}

class instructDialog : public QDialog
{
    Q_OBJECT

public:
    explicit instructDialog(QWidget *parent = nullptr);
    ~instructDialog();

private:
    Ui::instructDialog *ui;
};

#endif // INSTRUCTDIALOG_H
