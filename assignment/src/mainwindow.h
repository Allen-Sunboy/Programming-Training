#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "timeline.h"
#include "timelinewidget.h"

#include <QMainWindow>
#include <QCoreApplication>
#include <QScreen>
#include <QListWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QProgressDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //更新时间轴的内容与布局
    void setTimeList();

    //重载鼠标点击事件，用于判断是否时间轴内容被选中
    void mousePressEvent(QMouseEvent *event);

    //重载窗口大小变化事件，用于使某些部件的大小由此而变化
    void resizeEvent(QResizeEvent *event);

private slots:

    //导入视频
    void on_actionAddVideo_triggered();

    //导出视频
    void on_actionExport_triggered();

    //添加图片
    void on_actionAddImage_triggered();

    //添加文字素材
    void on_actionAddText_triggered();

    //添加字幕文件
    void on_actionAddCaption_triggered();

    //设置图片素材默认时长
    void on_actionImageDuration_triggered();

    //设置文字素材默认时长
    void on_actionTextDuration_triggered();

    //关于
    void on_actionInstruct_triggered();

    //图片素材右键菜单
    void on_listWidgetImage_customContextMenuRequested(const QPoint &pos);

    //文字素材右键菜单
    void on_tableWidgetText_customContextMenuRequested(const QPoint &pos);

    //视频列表右键菜单
    void on_listWidgetVideo_customContextMenuRequested(const QPoint &pos);

    //播放暂停键
    void on_pushButtonStartPause_clicked();

    //设置参数
    void on_pushButtonSet_clicked();

    //上移一层
    void on_pushButtonUp_clicked();

    //下移一层
    void on_pushButtonDown_clicked();

    //视频剪切
    void on_pushButtonCut_clicked();

    //视频切分
    void on_pushButtonDivide_clicked();

    //视频合并
    void on_pushButtonConcat_clicked();

    //生成预览视频
    void on_pushButtonForm_clicked();

    //移除字幕文件
    void on_pushButtonDeleteCaption_clicked();

    //删除选中对象
    void on_pushButtonDeleteObject_clicked();

    //播放器加载的视频的时长的变化，会更新进度条的最大值
    void onPlayerDurationChanged(qint64 dur);

    //播放器进度的变化，会更新进度条的滑块的位置
    void onPlayerPositionChanged(qint64 pos);

    //进度条滑块的移动，会更新播放器的进度
    void onSliderMoved(int value);

    //播放器状态的变化，会更新按图案
    void onPlayerStateChanged(QMediaPlayer::State state);

private:
    Ui::MainWindow *ui;

    //屏幕尺寸
    QSize screenSize;
    //屏幕width
    int screenWidth;
    //屏幕height
    int screenHeight;

    //允许的窗口最小width
    int minimumWidth;
    //允许的窗口最小height
    int minimumHeight;

    //图片素材的默认时长
    int imageDuration = 5;
    //文字素材的默认时长
    int textDuration = 5;

    //视频列表map，key是视频路径，value是视频名字
    QMap<QString, QString> videoList;

    //视频列表的视频名字list
    QStringList videoNameList;

    //图片素材map，key是图片路径，value是图片名字
    QMap<QString, QString> imageList;

    //图片素材库的图片名字list
    QStringList imageNameList;

    //文字素材map，key是文字素材内容，value是文字素材名字
    QMap<QString, QString> textList;


    //时间轴显示的总时长，默认为60秒，之后可根据需要而修改
    int wholeTime = 60;
    //时间轴刻度间隔，固定为150
    int interval = 150;

    QMediaPlayer *mediaPlayer;

    //时间轴对象的列表
    QList<timeLineWidget *> timeList;

    // 时间轴对象是否被选中
    QList<bool> chosen;
    //时间轴对象被选中的数量
    int chosenNum = 0;

    //程序所在路径
    QString currentDir = QCoreApplication::applicationDirPath();

    //用于显示显示字幕状态
    QLabel *labelCaption;
    //字幕文件的名字
    QString captionName;
    QString captionPath;

    //最后一次生成的预览视频的名字
    QString finalName;
    //最后一次生成的预览视频的路径
    QString finalPath;

    //生成的视频的格式，默认为mp4
    QString finalSuffix = "mp4";

    //命令行的运行的ffmpeg
    QString program = QCoreApplication::applicationDirPath() + "/ffmpeg/bin/ffmpeg.exe";

    //ffprobe
    QString program2 = QCoreApplication::applicationDirPath() + "/ffmpeg/bin/ffprobe.exe";

};
#endif // MAINWINDOW_H
