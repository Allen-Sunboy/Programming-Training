#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QLabel>
#include <QWidget>

class timeLineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit timeLineWidget(int t, QString name, QString path, int start, int dur, QWidget *parent = nullptr);

    QString getFileName();
    QString getFilePath();

    QString getTextContent();

    int getType();

    int getStart();
    int getDuration();

    int getX();
    int getY();

    int getEffectId();

    void setLabel();
    void setLabelChosen();
    void setLabelNotChosen();

    void setFileName(QString name);
    void setFilePath(QString path);

    void setStart(int start);
    void setDuration(int dur);

    void setX(int xx);
    void setY(int yy);

    void setEffectId(int i);


private:
    int type; //0是视频，1是图片，2是文字

    QString fileName; //视频，图片的名字
    QString filePath; //视频，图片的路径

    QString textName; //文字素材的名字
    QString textContent; //文字素材的内容

    QLabel *label; //时间轴显示的文字和横条

    int startTime; //文字或图片素材在时间轴的起始时间
    int duration; //文字或图片素材的时长

    bool isChosen = 0; //被选中

    int x = 0; //文字或图片的x坐标
    int y = 0; //文字或图片的y坐标

    int effectId = 0; //素材效果

    int interval = 150; //时间轴刻度间距，固定为150
};


#endif // TIMELINEWIDGET_H


