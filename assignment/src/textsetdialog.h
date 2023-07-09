#ifndef TEXTSETDIALOG_H
#define TEXTSETDIALOG_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class textSetDialog;
}

class textSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit textSetDialog(QWidget *parent = nullptr);
    ~textSetDialog();
    void showStartEnd(int start, int duration);
    void showXY(int x, int y);
    int getX();
    int getY();
    int getStart();
    int getDuration();

private:
    Ui::textSetDialog *ui;
};

#endif // TEXTSETDIALOG_H
