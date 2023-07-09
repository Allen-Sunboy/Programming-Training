#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>

namespace Ui {
class textDialog;
}

class textDialog : public QDialog
{
    Q_OBJECT

public:
    explicit textDialog(QWidget *parent = nullptr);
    QString getName();
    QString getContent();
    ~textDialog();

private:
    Ui::textDialog *ui;
};

#endif // TEXTDIALOG_H
