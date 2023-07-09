#include "timeline.h"

#include <QDebug>

timeLine::timeLine(QWidget *parent)
    : QWidget{parent}
{
    this->resize(interval * wholeTime, 100 + num * 50);
}

void timeLine::paintEvent(QPaintEvent *event)
{
    lineList.clear();
    for(int i = 0, k = 0; i < wholeTime; i++, k += interval)
    {
        QLine line(k, 0, k, 30);
        lineList.append(line);
    }

    QPainter painter(this);
    QTime time = QTime(0, 0, 0);

    for(int i = 0, k = 0; i < lineList.size(); i++, k++)
    {
        painter.drawLine(lineList[k]);

        QString strValue = time.toString("hh:mm:ss");
        int fontWidth = fontMetrics().horizontalAdvance(strValue) / 2;
        painter.drawText(QPointF(lineList[k].x1() - fontWidth, 50), strValue);

        painter.drawLine(lineList[k].x1(), 0, lineList[k].x1() + interval, 0); //水平线

        time = time.addSecs(1); //设置刻度的间隔为1秒
    }
}

void timeLine::setNum(int n)
{
    num = n;
    resize(interval * wholeTime, 100 + num * 50);
}

void timeLine::setWholeTime(int w)
{
    if(w > wholeTime)
    {
        wholeTime = w;
        resize(interval * wholeTime, 100 + num * 50);
    }
}

