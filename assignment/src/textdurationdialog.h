#ifndef TEXTDURATIONDIALOG_H
#define TEXTDURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class textDurationDialog;
}

class textDurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit textDurationDialog(QWidget *parent = nullptr);
    ~textDurationDialog();
    int getDuration();
    void showDuration(int i);

private:
    Ui::textDurationDialog *ui;
};

#endif // TEXTDURATIONDIALOG_H
