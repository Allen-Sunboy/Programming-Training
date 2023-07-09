#ifndef IMAGEDURATIONDIALOG_H
#define IMAGEDURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class imageDurationDialog;
}

class imageDurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit imageDurationDialog(QWidget *parent = nullptr);
    ~imageDurationDialog();
    int getDuration();
    void showDuration(int i);

private:
    Ui::imageDurationDialog *ui;
};

#endif // IMAGEDURATIONDIALOG_H
