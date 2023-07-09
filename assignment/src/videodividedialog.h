#ifndef VIDEODIVIDEDIALOG_H
#define VIDEODIVIDEDIALOG_H

#include <QDialog>

namespace Ui {
class videoDivideDialog;
}

class videoDivideDialog : public QDialog
{
    Q_OBJECT

public:
    explicit videoDivideDialog(QWidget *parent = nullptr);
    ~videoDivideDialog();
    void showDuration(int duration);
    int getTime();


private:
    Ui::videoDivideDialog *ui;
};

#endif // VIDEODIVIDEDIALOG_H
