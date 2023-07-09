#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

#include <QWidget>

namespace Ui {
class mediawidget;
}

class mediawidget : public QWidget
{
    Q_OBJECT

public:
    explicit mediawidget(QWidget *parent = nullptr);
    ~mediawidget();

private:
    Ui::mediawidget *ui;
};

#endif // MEDIAWIDGET_H
