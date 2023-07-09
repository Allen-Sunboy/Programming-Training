#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QPainter>
#include <QTime>


class timeLine : public QWidget
{
    Q_OBJECT
public:
    explicit timeLine(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    void setNum(int n);

    void setWholeTime(int w);


private:
    QList<QLine> lineList; //刻度线

    int interval = 150; //刻度之间的间隔，固定为150

    int wholeTime = 60; //时间轴显示的总时长，默认为60，可修改

    int num = 20; //时间轴的内容的总数量，默认为20

};

#endif // TIMELINE_H

