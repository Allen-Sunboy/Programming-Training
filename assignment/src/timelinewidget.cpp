#include "timelinewidget.h"
#include <QDebug>


timeLineWidget::timeLineWidget(int Type, QString str1, QString str2, int start, int dur, QWidget *parent):
    QWidget{parent}, type(Type), startTime(start), duration(dur)
{
    if(Type == 0 || Type == 1)
    {
        fileName = str1;
        filePath = str2;
    }
    if(Type == 2)
    {
        textName = str1;
        textContent = str2;
    }

    label = new QLabel(this);
}

QString timeLineWidget::getFileName()
{
    return fileName;

}

QString timeLineWidget::getFilePath()
{
    return filePath;

}

QString timeLineWidget::getTextContent()
{
    return textContent;
}

int timeLineWidget::getType()
{
    return type;
}

int timeLineWidget::getStart()
{
    return startTime;
}

int timeLineWidget::getDuration()
{
    return duration;
}

int timeLineWidget::getX()
{
    return x;
}

int timeLineWidget::getY()
{
    return y;
}

int timeLineWidget::getEffectId()
{
    return effectId;
}



void timeLineWidget::setFileName(QString name)
{
    fileName = name;

}

void timeLineWidget::setFilePath(QString path)
{
    filePath = path;

}

void timeLineWidget::setStart(int start)
{
    startTime = start;

}

void timeLineWidget::setDuration(int dur)
{
    duration = dur;
}

void timeLineWidget::setX(int xx)
{
    x = xx;
}

void timeLineWidget::setY(int yy)
{
    y = yy;
}

void timeLineWidget::setLabel()
{
    QString str;
    if(type == 0)
    {
        str += "[视频]";
    }
    if(type == 1)
    {
        str += "[图片]";
    }
    if(type == 2)
    {
        str += "[文字]";
    }
    if(fileName != NULL)
    {
        str += fileName;
    }
    else
    {
        str += textName;
    }
    label->setText(str);

    label->setGeometry(startTime * 150, 0, duration * 150, 50);
}

void timeLineWidget::setLabelChosen()
{
    label->setStyleSheet(QString("background:") + "yellow");
}

void timeLineWidget::setLabelNotChosen()
{
    label->setStyleSheet(QString("background:") + "gray");
}

void timeLineWidget::setEffectId(int i)
{
    effectId = i;
}

