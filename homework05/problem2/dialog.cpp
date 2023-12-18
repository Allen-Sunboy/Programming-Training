#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(400, 300);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(check()));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::check()
{

    static QRegularExpression isnum("^[1-9][0-9]{0,}$"); //年月日的开头不能是0
    QString yearStr = ui->lineEditYear->text();
    bool matchYear = isnum.match(yearStr).hasMatch();
    qint64 yearNum = yearStr.toInt();
    bool isLeapYear = 0; //闰年特判
    if (yearNum % 4 == 0 && !(yearNum % 100 == 0 && yearNum % 400 != 0))
    {
        isLeapYear = 1;
    }
    bool isYearValid = 0;
    if (matchYear)
    {
        isYearValid = 1;
    }

    QString monthStr = ui->lineEditMonth->text();
    bool matchMonth = isnum.match(monthStr).hasMatch();
    qint64 monthNum = monthStr.toInt();
    bool isMonthValid = 0;
    if (matchMonth && monthNum <= 12 && monthNum >= 1)
    {
        isMonthValid = 1;
    }

    QString dayStr = ui->lineEditDay->text();
    bool matchDay = isnum.match(dayStr).hasMatch();
    qint64 month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //月份数组
    if (isLeapYear) //闰年特判
    {
        month[2] = 29;
    }

    bool isDayValid = 0;
    qint64 dayNum = dayStr.toInt();
    if (matchDay && dayNum >= 1 && dayNum <= month[monthNum])
    {
        isDayValid = 1;
    }

    if (isYearValid && isMonthValid && isDayValid)
    {
        QString output = "你输入的日期是：" + yearStr + "年" + monthStr + "月" + dayStr + "日";
        QMessageBox::information(this, "输入结果", output);
    }
    else
    {
        QMessageBox::critical(this, "输入结果", "您输入的年月日中存在不合法的数据！");
    }

}
