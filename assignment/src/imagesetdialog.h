#ifndef IMAGESETDIALOG_H
#define IMAGESETDIALOG_H

#include <QDialog>

#include <QButtonGroup>

namespace Ui {
class imageSetDialog;
}

class imageSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit imageSetDialog(QWidget *parent = nullptr);
    ~imageSetDialog();

    void showStartEnd(int start, int duration);
    void showXY(int x, int y);
    void showEffectId(int i);

    int getX();
    int getY();
    int getStart();
    int getDuration();
    int getEffectId();


private:
    Ui::imageSetDialog *ui;
    QButtonGroup *group;

};

#endif // IMAGESETDIALOG_H
