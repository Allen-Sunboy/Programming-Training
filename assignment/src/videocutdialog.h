#ifndef VIDEOCUTDIALOG_H
#define VIDEOCUTDIALOG_H

#include <QDialog>

namespace Ui {
class videoCutDialog;
}

class videoCutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit videoCutDialog(QWidget *parent = nullptr);
    ~videoCutDialog();

    int getNewStart();
    int getNewDuration();

    void showDuration(int duration);

private:
    Ui::videoCutDialog *ui;
};

#endif // VIDEOCUTDIALOG_H
