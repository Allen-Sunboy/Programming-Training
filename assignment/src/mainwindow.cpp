#include "imagedurationdialog.h"
#include "textdurationdialog.h"
#include "instructdialog.h"

#include "textdialog.h"

#include "imagesetdialog.h"
#include "textsetdialog.h"

#include "videocutdialog.h"
#include "videodividedialog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QMouseEvent>
#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取屏幕大小信息
    QScreen *screen = QGuiApplication::primaryScreen();
    screenSize = screen->availableSize();
    screenWidth = screenSize.width();
    screenHeight = screenSize.height();

    //初始化主窗口
    int mainWidth = screenWidth - 300;
    int mainHeight = screenHeight - 300;
    setGeometry(100, 100, mainWidth, mainHeight);

    //初始化图片素材库
    ui->listWidgetImage->setIconSize(QSize(100, 100)); //设置展示的图片大小
    //图片素材库加滚动条
    ui->listWidgetImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->listWidgetImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //初始化文字素材库
    //设置表头
    QStringList header;
    header << "文字素材名" << "文字素材内容";
    ui->tableWidgetText->setHorizontalHeaderLabels(header);
    //文字素材库加滚动条
    ui->tableWidgetText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->tableWidgetText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //初始化视频列表
    //视频列表加上滚动条
    ui->listWidgetVideo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->listWidgetVideo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //初始化时间轴
    //设置时间轴区域的widget不会自动调整大小，否则无法手动设置widget大小
    ui->scrollAreaTimeLine->setWidgetResizable(false);

    //时间轴区域加上滚动条
    ui->scrollAreaTimeLine->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollAreaTimeLine->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //初始化时间轴区域的位置信息
    ui->timeLineContent->setGeometry(0, 0, wholeTime * interval, 100 + 20 * 50);

    labelCaption = new QLabel("当前载入的字幕文件名：", ui->timeLineContent);
    labelCaption->setGeometry(0, 50, 600, 50);

    //初始化预览窗口
    ui->scrollAreaVideo->setWidgetResizable(false);

    ui->pushButtonStartPause->setIconSize(ui->pushButtonStartPause->size());
    ui->pushButtonStartPause->setIcon(QPixmap(":/icon/icon/start.png"));

    ui->videoWidget->setGeometry(0, 0, mainWidth * 0.5, mainHeight * 0.5 - 150);

    mediaPlayer = new QMediaPlayer;
    mediaPlayer->setVideoOutput(ui->videoWidget);

    mediaPlayer->setMedia(QMediaContent());

    //信号，播放器加载的视频的时长的变化
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(onPlayerDurationChanged(qint64)));

    //信号，播放器的播放进度的变化
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPlayerPositionChanged(qint64)));

    //信号，进度条的位置的变化
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(onSliderMoved(int)));

    //信号，播放器的状态的变化
    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onPlayerStateChanged(QMediaPlayer::State)));

    //每次运行程序都会清空目录下的temp文件夹的内容，一个便捷的处理方法是，直接删掉这个文件夹，再新建一个空的
    QString tempDir = currentDir + "/temp";
    QDir dir(tempDir);
    dir.removeRecursively();
    dir.setPath(tempDir);
    if(dir.isEmpty())
    {
        dir.mkdir(tempDir);
    }

    //图片素材重命名的信号槽
    connect(ui->listWidgetImage, &QListWidget::itemChanged, this, [=](){
        QListWidgetItem *item = ui->listWidgetImage->currentItem();

        //导入图片时也会发射该信号，需要先判断是否是这种情况，如果是，则currentItem为NULL，返回
        if(item == NULL)
        {
            return;
        }

        int count = imageNameList.size();
        int currentRow = ui->listWidgetImage->currentRow();
        QString previousName = imageNameList[currentRow];

        QString filePath = imageList.key(previousName);

        QString newName = ui->listWidgetImage->currentItem()->text();
        for(int i = 0; i < count; i++)
        {
            if(ui->listWidgetImage->item(i)->text() == newName && i != currentRow)
            {
                QMessageBox::information(this, "提示", "该名字已存在！");
                item->setText(previousName);
                return;
            }
        }
        imageNameList[currentRow] = newName;
        imageList[filePath] = newName;

    });

    //文字素材重命名
    connect(ui->tableWidgetText, &QTableWidget::itemChanged, this, [=](){

        //添加文字素材时也会发射此信号，需要先判断是否是这种情况，如果是则返回
        int column = ui->tableWidgetText->currentColumn();
        if(column == -1)
        {
            return;
        }
        int row = ui->tableWidgetText->currentRow();

        QTableWidgetItem *item = ui->tableWidgetText->currentItem();
        //修改的是文字素材的名字
        if(column == 0)
        {
            QString name = item->text();
            QString content = ui->tableWidgetText->item(row, 1)->text();
            if(textList.key(name) != content && textList.key(name) != NULL)
            {
                QMessageBox::information(this, "提示", "该素材名字已存在！");
                item->setText(textList[content]);
                return;
            }
            textList[content] = name;

        }
        //修改的是文字素材的内容
        if(column == 1)
        {
            QString name = ui->tableWidgetText->item(row, 0)->text();
            QString content = item->text();
            //test
            if(textList[content] != name && textList[content] != NULL)
            {
                QMessageBox::information(this, "提示", "该素材内容已存在！");
                item->setText(textList.key(name));

                return;
            }
            textList.remove(textList.key(name));
            textList.insert(content, name);
        }
    });

    //视频重命名
    connect(ui->listWidgetVideo, &QListWidget::itemChanged, this, [=](){
        QListWidgetItem *item = ui->listWidgetVideo->currentItem();

        //导入视频时也会发射该信号，需要先判断是否是这种情况，如果是，则currentItem为NULL，返回
        if(item == NULL)
        {
            return;
        }

        int count = videoNameList.size();
        int currentRow = ui->listWidgetVideo->currentRow();
        QString previousName = videoNameList[currentRow];

        QString filePath = videoList.key(previousName);

        QString newName = ui->listWidgetVideo->currentItem()->text();
        for(int i = 0; i < count; i++)
        {
            if(ui->listWidgetVideo->item(i)->text() == newName && i != currentRow)
            {
                QMessageBox::information(this, "提示", "该名字已存在！");
                item->setText(previousName);
                return;
            }
        }
        videoNameList[currentRow] = newName;
        videoList[filePath] = newName;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    int mainWidth = this->width();
    int mainHeight = this->height();
    ui->videoWidget->resize(mainWidth * 0.5, mainHeight * 0.5 - 150);
}

//设置图片素材默认时长
void MainWindow::on_actionImageDuration_triggered()
{
    imageDurationDialog *dlg = new imageDurationDialog(this);
    dlg->showDuration(imageDuration);
    if(dlg->exec() == QDialog::Accepted)
    {
        imageDuration = dlg->getDuration();
    }

}

//设置文字素材默认时长
void MainWindow::on_actionTextDuration_triggered()
{
    textDurationDialog *dlg = new textDurationDialog(this);
    dlg->showDuration(textDuration);

    if(dlg->exec() == QDialog::Accepted)
    {
        textDuration = dlg->getDuration();
    }

}


void MainWindow::setTimeList()
{
    int size = timeList.size();
    ui->timeLineContent->setNum(size + 1);
    chosen.clear();
    for(int i = 0; i < size; i++)
    {
        timeList[i]->setGeometry(0, 100 + i * 50, 40000, 50);

        //最上面的视频设置起始时间为第0秒，下一个视频开始时，上一个视频刚好结束，也就是保证视频连续
        if(timeList[i]->getType() == 0)
        {
            if(i == 0)
            {
                timeList[i]->setStart(0);
            }
            else
            {
                int preVideo = i;
                for(int j = i - 1; j >= 0; j--)
                {
                    if(timeList[j]->getType() == 0)
                    {
                        preVideo = j;
                        break;
                    }
                }
                if(preVideo == i)
                {
                    timeList[i]->setStart(0);
                }
                else
                {
                    timeList[i]->setStart(timeList[preVideo]->getStart() + timeList[preVideo]->getDuration());
                }
            }
        }
        timeList[i]->setLabel();
        timeList[i]->setLabelNotChosen();
        timeList[i]->show();
        chosen.append(0);
    }

    int maxTime = 0;
    for(int i = 0; i < size; i++)
    {
        maxTime = std::max(maxTime, timeList[i]->getStart() +timeList[i]->getDuration());
    }
    ui->timeLineContent->setWholeTime(maxTime);

    chosenNum = 0;
}

//生成预览视频
void MainWindow::on_pushButtonForm_clicked()
{


    int size = timeList.size();
    if(size == 0)
    {
        QMessageBox::information(this, "生成失败", "当前时间轴中没有视频！");
        return;
    }
    QList<timeLineWidget *> videoTimeList;
    QList<timeLineWidget *> imageTimeList;
    QList<timeLineWidget *> textTimeList;

    for(int i = 0; i < size; i++)
    {
        if(timeList[i]->getType() == 0)
        {
            videoTimeList.append(timeList[i]);
            continue;
        }
        if(timeList[i]->getType() == 1)
        {
            imageTimeList.append(timeList[i]);
            continue;
        }
        if(timeList[i]->getType() == 2)
        {
            textTimeList.append(timeList[i]);
            continue;
        }
    }
    int vSize = videoTimeList.size();

    if(vSize == 0)
    {
        QMessageBox::information(this, "生成失败", "当前时间轴中没有视频！");
        return;
    }
    QProgressDialog *progress = new QProgressDialog();

    progress->setWindowModality(Qt::WindowModal);
    progress->setAttribute(Qt::WA_DeleteOnClose, true);
    progress->setCancelButtonText(NULL);
    progress->setWindowTitle("生成预览视频中");
    progress->setLabelText("合成视频中");
    progress->setRange(0, 100);
    progress->setMinimumDuration(0);

    QCoreApplication::processEvents();

    progress->setValue(0);

    //先把第一个文件复制到temp目录
    QString suffix0 = QFileInfo(videoTimeList[0]->getFilePath()).suffix();

    QString str0 = "0" + QDateTime::currentDateTime().toString("-yy-MM-dd-hh-mm-ss-zzz");

    QString latestName = str0 + "." + suffix0;

    QString latestPath = currentDir + "/temp/" + latestName;
    QFile::copy(videoTimeList[0]->getFilePath(), latestPath);

    //如果视频数大于1

    if(vSize > 1)
    {
        for(int i = 1; i < vSize; i++)
        {
            QString name1 = latestName;
            QString path1 = latestPath;

            QString name2 = videoTimeList[i]->getFileName();
            QString path2 = videoTimeList[i]->getFilePath();

            QString ts1 = QFileInfo(name1).baseName();

            ts1.append(".ts");

            QString ts1Path = currentDir + "/temp/" + ts1;

            QStringList arg1;
            arg1.clear();
            arg1 << "-i" << path1
                 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts"
                 << ts1Path;

            QProcess::execute(program, arg1);

            QString currentDateTime2 = QDateTime::currentDateTime().toString("-yy-MM-dd-hh-mm-ss-zzz");

            QString ts2 = QFileInfo(name2).baseName();

            ts2.append(currentDateTime2);
            ts2.append(".ts");

            QString ts2Path = currentDir + "/temp/" + ts2;

            QStringList arg2;
            arg2.clear();

            arg2 << "-i" << path2
                 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts"
                 << ts2Path;

            QProcess::execute(program, arg2);

            QDateTime t = QDateTime::currentDateTime();

            //保险起见，给t加1毫秒
            t = t.addMSecs(1);

            QString currentDateTime3 = t.toString("-yy-MM-dd-hh-mm-ss-zzz");

            QString txtName = currentDateTime3 + ".txt";
            QString txtPath = currentDir + "/temp/" + txtName;

            QFile file(txtPath);
            file.open(QIODevice::Append|QIODevice::Text);
            QTextStream stream(&file);
            stream << "file " << "\'" << ts1 << "\'" << "\n"
                   << "file " << "\'" << ts2 << "\'" ;
            file.close();

            QString numStr;
            numStr = numStr.setNum(i);

            latestName = numStr + QDateTime::currentDateTime().toString("-yy-MM-dd-hh-mm-ss-zzz");
            latestName += "." + finalSuffix;
            latestPath = currentDir + "/temp/" + latestName;

            QStringList arg3;
            arg3.clear();

            arg3 << "-f" << "concat"
                 << "-i" << txtPath
                 << "-c" << "copy"
                 << latestPath;

            QProcess::execute(program, arg3);
        }
    }
    progress->setLabelText("添加图片中");
    progress->setValue(25);

    //添加图片

    int iSize = imageTimeList.size();
    if(iSize >= 1)
    {
        for(int i = 0; i < iSize; i++)
        {
            QString prePath = latestPath;

            QString numStr;
            numStr.setNum(i);
            QString cur = QDateTime::currentDateTime().toString("-yy-MM-dd-hh-mm-ss-zzz");

            QString name = imageTimeList[i]->getFileName();
            QString path = imageTimeList[i]->getFilePath();

            int x = imageTimeList[i]->getX();
            int y = imageTimeList[i]->getY();

            QString xStr;
            xStr.setNum(x);
            QString yStr;
            yStr.setNum(y);
            int start = imageTimeList[i]->getStart();
            int dur = imageTimeList[i]->getDuration();

            QString str1;
            str1.setNum(start);
            QString str2;
            str2.setNum(start+dur);

            QString str3;
            str3.setNum(dur);

            latestName = numStr + cur;
            latestName += "." + finalSuffix;

            latestPath = currentDir + "/temp/" + latestName;

            //无效果
            if(imageTimeList[i]->getEffectId() == 0)
            {
                QString s1 = "overlay=x=";
                s1 += xStr + ":y=" + yStr + ":enable=between(t\\," + str1 + "\\," + str2 + ")";
                QStringList arg;
                arg << "-i" << prePath
                    << "-i" << path
                    << "-filter_complex" << s1
                    << latestPath;

                QProcess::execute(program, arg);
            }

            //淡入淡出
            if(imageTimeList[i]->getEffectId() == 1)
            {
                //淡入淡出持续时间
                QString str4;
                str4.setNum(0.5);

                //淡出的时间
                QString str5;
                str5.setNum(start + dur - 0.5);
                QString s1 = "[1:v]fade=in:st=";
                s1 += str1 + ":d=" + str4 + ":alpha=1,fade=out:st=" + str5 + ":d=" + str4 + ":alpha=1[water];[0][water]overlay=x="
                        + xStr + ":y=" + yStr + ":enable=between(t\\," + str1 + "\\," + str2 + "):shortest=1";

                QStringList arg;
                arg << "-i" << prePath
                    << "-loop" << "1"
                    << "-i" << path
                    << "-filter_complex" << s1 << "-y"
                    << latestPath;
                QProcess::execute(program, arg);
            }

            //平移
            if(imageTimeList[i]->getEffectId() == 2)
            {

                QString s1 = "overlay=x=";
                s1 += xStr + "+t*150:y=" + yStr + ":enable=between(t\\," + str1 + "\\," + str2 + ")";
                QStringList arg;
                arg << "-i" << prePath
                    << "-i" << path
                    << "-lavfi" << s1
                    << latestPath;

                QProcess::execute(program, arg);

            }

            //旋转
            if(imageTimeList[i]->getEffectId() == 3)
            {
                QString s1 = "[1:v]format=rgba,rotate=PI/2*t:c=0x00000000:ow=hypot(iw\\,ih):oh=ow[out];[0:v][out]overlay=x=";
                s1 += xStr + ":y=" + yStr + ":enable=between(t\\," + str1 + "\\," + str2 + "):shortest=1";
                QStringList arg;
                arg << "-i" << prePath
                    << "-loop" << "1"
                    << "-i" << path
                    << "-lavfi" << s1
                    << latestPath;

                QProcess::execute(program, arg);
            }
        }
    }

    progress->setLabelText("添加文字中");
    progress->setValue(50);

    //添加文字
    int tSize = textTimeList.size();
    if(tSize >= 1)
    {
        for(int i = 0; i < tSize; i++)
        {
            QString prePath = latestPath;

            QString numStr;
            numStr.setNum(i);

            QString cur = QDateTime::currentDateTime().toString("-yy-MM-dd-hh-mm-ss-zzz");

            latestName = numStr + cur + "." + finalSuffix;

            latestPath = currentDir + "/temp/" + latestName;

            QString text = textTimeList[i]->getTextContent();

            int x = textTimeList[i]->getX();
            int y = textTimeList[i]->getY();

            QString xStr;
            xStr.setNum(x);
            QString yStr;
            yStr.setNum(y);
            int start = textTimeList[i]->getStart();
            int dur = textTimeList[i]->getDuration();

            QString str1;
            str1.setNum(start);
            QString str2;
            str2.setNum(start + dur);


            QString str = "drawtext=fontsize=50:text=";
            str += "\'" + text + "\'" + ":x=" + xStr + ":y=" +yStr + ":enable=\'between(t\\,"
                    + str1 + "\\," + str2 + ")\'";

            QStringList arg;
            arg << "-i" << prePath
                << "-vf" << str << "-y"
                << latestPath;

            QProcess::execute(program, arg);

        }
    }
    progress->setLabelText("添加字幕中");
    progress->setValue(75);

    //添加字幕 路径是正斜杠 用单引号引起来 用反斜杠转义
    if(captionPath != NULL)
    {
        latestName = "0" + QDateTime::currentDateTime().toString("-yy-MM-dd-hh-mm-ss-zzz") + "." + finalSuffix;
        QString prePath = latestPath;
        latestPath = currentDir + "/temp/" + latestName;
        QString str = "subtitles=";
        str += "\\\'" + captionPath + "\\\'";
        QStringList arg;
        arg << "-i" << prePath
            << "-vf" << str
            << latestPath;

        QProcess::execute(program, arg);
    }
    progress->setValue(100);

    QMessageBox::information(this, "提示", "生成预览视频成功，视频加载到播放器需要一点时间，建议不要立即点击播放按钮预览，"
                                         "如果播放失败，可再点击\"生成预览视频\"按钮，重新生成视频");

    finalName = latestName;
    finalPath = latestPath;

    mediaPlayer->setMedia(QMediaContent());


    mediaPlayer->setMedia(QUrl::fromLocalFile(finalPath));

    setTimeList();

}


//时间轴对象选择
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int mouseX = event->globalPos().x();
    int mouseY = event->globalPos().y();
    if(timeList.empty())
    {
        return;
    }
    int size = timeList.size();

    for(int i = 0; i < size; i++)
    {
        if(ui->timeLineContent->mapToGlobal(timeList[i]->pos()).x() <= mouseX
                && ui->timeLineContent->mapToGlobal(timeList[i]->pos()).y() <= mouseY
                && ui->timeLineContent->mapToGlobal(timeList[i]->pos()).x() + timeList[i]->width() >= mouseX
                && ui->timeLineContent->mapToGlobal(timeList[i]->pos()).y() + timeList[i]->height() >= mouseY)
        {
            if(chosen[i])
            {
                timeList[i]->setLabelNotChosen();
                chosen[i] = 0;
                chosenNum--;
            }
            else
            {
                timeList[i]->setLabelChosen();
                chosen[i] = 1;
                chosenNum++;
            }
            return;
        }
    }

}


//导入图片到素材库
void MainWindow::on_actionAddImage_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "选择图片文件", "C:\\", "图片文件 (*.png *.jpg)");

    //获取每个图片文件的信息并添加到list
    for(QString &i : files)
    {
        QFileInfo fileInfo = QFileInfo(i);
        QString fileName = fileInfo.fileName();

        QString filePath = fileInfo.filePath();

        if(imageList[filePath] != NULL)
        {
            QMessageBox::information(this, "提示", "该图片已存在！");
            return;
        }

        if(fileName != NULL) //判断是否之前选择了某个文件
        {
            //如果素材库中已存在一个名字相同但文件路径不同的图片，则将这个新加的图片的名字改为全路径
            if(videoList.key(fileName) != NULL && videoList.key(fileName) != filePath)
            {
                fileName = filePath;
            }
            QListWidgetItem *it = new QListWidgetItem(QIcon(filePath), fileName, ui->listWidgetImage);
            it->setSizeHint(QSize(ui->listWidgetImage->width(), 100));

            //设置名字可编辑
            it->setFlags(it->flags() | Qt::ItemIsEditable);
            ui->listWidgetImage->addItem(it);

            imageList.insert(filePath, fileName);
            imageNameList.append(fileName);
        }
    }

}

//图片素材的右键操作
void MainWindow::on_listWidgetImage_customContextMenuRequested(const QPoint &pos)
{
    //获取鼠标右键时所在的item
    QListWidgetItem *item = ui->listWidgetImage->itemAt(pos);

    //判断右键时是否鼠标是在某个item上，如果不是则return
    if(item == NULL)
    {
        return;
    }
    QMenu *menuImage = new QMenu(this);
    QAction *actionDelete = new QAction("删除", this);
    QAction *actionAddtoTimeline = new QAction("添加到时间轴", this);
    menuImage->addAction(actionDelete);
    menuImage->addAction(actionAddtoTimeline);

    QString fileName = item->text();
    QString filePath = imageList.key(fileName);

    int row = ui->listWidgetImage->currentRow();

    //图片素材的重命名，可直接双击修改

    //图片素材删除
    connect(actionDelete, &QAction::triggered, this, [=](){
        imageList.remove(filePath);
        imageNameList.removeAt(row);
        ui->listWidgetImage->removeItemWidget(item);
        delete item;

    });
    //图片素材添加到时间轴
    connect(actionAddtoTimeline, &QAction::triggered, this, [=](){
        timeLineWidget *timelinewidget = new timeLineWidget(1, fileName, filePath, 0, imageDuration, ui->timeLineContent);
        timeList.append(timelinewidget);
        setTimeList();
    });

    menuImage->exec(QCursor::pos());
}

//导入文字到文字素材库
void MainWindow::on_actionAddText_triggered()
{
    textDialog *dlg = new textDialog(this);
    if(dlg->exec() == QDialog::Accepted)
    {
        QString name = dlg->getName();
        QString content = dlg->getContent();

        if(name != NULL && content != NULL)
        {
            if(textList[content] != NULL)
            {
                QMessageBox::information(this, "提示", "该文字素材的内容已存在！");
                return;
            }
            if(textList.key(name) != NULL)
            {
                QMessageBox::information(this, "提示", "该文字素材的名字已存在！");
                return;
            }
            QTableWidgetItem *itemName = new QTableWidgetItem(name);
            QTableWidgetItem *itemContent = new QTableWidgetItem(content);
            ui->tableWidgetText->setRowCount(ui->tableWidgetText->rowCount() + 1);
            ui->tableWidgetText->setItem(ui->tableWidgetText->rowCount() - 1, 0, itemName);
            ui->tableWidgetText->setItem(ui->tableWidgetText->rowCount() - 1, 1, itemContent);
            textList.insert(content, name);

        }

    }
}

//文字素材库的右键操作
void MainWindow::on_tableWidgetText_customContextMenuRequested(const QPoint &pos)
{
    //获取鼠标右键时所在的item
    QTableWidgetItem *item = ui->tableWidgetText->itemAt(pos);
    //判断右键时是否鼠标是在某个item上，如果不是则return
    if(item == NULL)
    {
        return;
    }
    QMenu *menuText = new QMenu(this);
    QAction *actionDelete = new QAction("删除", this);
    QAction *actionAddtoTimeLine = new QAction("添加到时间轴", this);
    menuText->addAction(actionDelete);
    menuText->addAction(actionAddtoTimeLine);

    int row = item->row();

    QString textName = ui->tableWidgetText->item(row, 0)->text();
    QString textContent = ui->tableWidgetText->item(row, 1)->text();

    //文字素材的重命名是直接在表格相应位置双击

    //文字素材删除
    connect(actionDelete, &QAction::triggered, this, [=](){
        ui->tableWidgetText->removeRow(row);
        textList.remove(textContent);

    });

    //文字素材添加到时间轴
    connect(actionAddtoTimeLine, &QAction::triggered, this, [=](){
        timeLineWidget *timelinewidget = new timeLineWidget(2, textName, textContent, 0, textDuration, ui->timeLineContent);

        timeList.append(timelinewidget);
        setTimeList();

    });

    menuText->exec(QCursor::pos());

}

//添加视频到视频列表
void MainWindow::on_actionAddVideo_triggered()
{

    QStringList files = QFileDialog::getOpenFileNames(this, "选择视频文件", "C:\\", "视频文件 (*.mp4 *.avi *.mov)");

    //获取每个视频文件的信息并添加到list
    for(QString &i : files)
    {
        QFileInfo fileInfo = QFileInfo(i);
        QString fileName = fileInfo.fileName();
        QString filePath = fileInfo.filePath();
        if(videoList[filePath] != NULL)
        {
            QMessageBox::information(this, "提示", "该视频已存在！");
            return;
        }

        if(fileName != NULL) //判断是否之前选择了某个文件
        {
            //如果视频列表中已存在一个名字相同但文件路径不同的视频，则将这个新加的视频的名字改为全路径
            if(videoList.key(fileName) != NULL && videoList.key(fileName) != filePath)
            {
                fileName = filePath;
            }
            QListWidgetItem *it = new QListWidgetItem(QIcon(":/icon/icon/video.png"), fileName, ui->listWidgetVideo);

            //设置名字可编辑
            it->setFlags(it->flags()|Qt::ItemIsEditable);
            ui->listWidgetVideo->addItem(it);
            videoList.insert(filePath, fileName);
            videoNameList.append(fileName);
        }
    }
}


void MainWindow::on_listWidgetVideo_customContextMenuRequested(const QPoint &pos)
{
    //获取鼠标右键时所在的item
    QListWidgetItem *item = ui->listWidgetVideo->itemAt(pos);

    //判断右键时是否鼠标是在某个item上，如果不是则return
    if(item == NULL)
    {
        return;
    }
    QMenu *menuVideo = new QMenu(this);
    QAction *actionDelete = new QAction("删除", this);
    QAction *actionAddtoTimeline = new QAction("添加到时间轴", this);
    menuVideo->addAction(actionDelete);
    menuVideo->addAction(actionAddtoTimeline);

    QString fileName = item->text();
    QString filePath = videoList.key(fileName);

    int row = ui->listWidgetVideo->currentRow();

    //视频的重命名可通过直接双击得到

    //视频删除
    connect(actionDelete, &QAction::triggered, this, [=](){
        videoList.remove(filePath);
        videoNameList.removeAt(row);

        ui->listWidgetVideo->removeItemWidget(item);
        delete item;

    });

    //视频添加到时间轴
    connect(actionAddtoTimeline, &QAction::triggered, this, [=](){

        QProcess *process = new QProcess(this);
        QStringList arg;
        arg << "-i" << filePath
            << "-show_entries" << "format=duration" << "-v" << "quiet" << "-of" << "csv=p=0";
        process->start(program2, arg);
        process->waitForFinished();
        QString str = process->readAllStandardOutput();

        int dur = str.toDouble();

        timeLineWidget *timelinewidget = new timeLineWidget(0, fileName, filePath, 0, dur, ui->timeLineContent);
        timeList.append(timelinewidget);
        setTimeList();
    });

    menuVideo->exec(QCursor::pos());

}


//导入字幕文件
void MainWindow::on_actionAddCaption_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "选择字幕文件", "C:\\", "字幕文件 (*.srt *.ass *.vtt)");

    QFileInfo fileInfo = QFileInfo(file);
    QString fileName = fileInfo.fileName();
    QString filePath = fileInfo.filePath();

    if(fileName != NULL)
    {
        captionName = fileName;
        captionPath = filePath;
        QString str = "当前载入的字幕文件名：" + captionName;
        labelCaption->setText(str);
    }
}


void MainWindow::on_actionExport_triggered()
{
    if(finalName == NULL)
    {
        QMessageBox::information(this, "提示", "尚无任何预览视频的版本，需先生成预览视频！");
        return;
    }
    QString dirPath = QFileDialog::getSaveFileName(this, "导出视频", "C:\\", QString("视频文件 (*.mp4)"));
    if(dirPath != NULL)
    {
        QFile::copy(finalPath, dirPath);
    }
}


//使用说明
void MainWindow::on_actionInstruct_triggered()
{
    instructDialog *dlg = new instructDialog(this);
    dlg->exec();
}


void MainWindow::onPlayerDurationChanged(qint64 dur)
{
    ui->horizontalSlider->setMaximum(dur);
}


void MainWindow::onPlayerPositionChanged(qint64 pos)
{
    ui->horizontalSlider->setValue(pos);
}


void MainWindow::onSliderMoved(int value)
{
    mediaPlayer->setPosition(value);

}


void MainWindow::onPlayerStateChanged(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PlayingState)
    {
        ui->pushButtonStartPause->setIcon(QPixmap(":/icon/icon/pause.png"));
    }
    else
    {
        ui->pushButtonStartPause->setIcon(QPixmap(":/icon/icon/start.png"));
    }

}

//播放暂停按钮
void MainWindow::on_pushButtonStartPause_clicked()
{
    if(mediaPlayer->mediaStatus() == QMediaPlayer::LoadingMedia)
    {
        return;
    }
    if(mediaPlayer->state() == QMediaPlayer::PlayingState)
    {
        mediaPlayer->pause();
        return;
    }
    else
    {
        mediaPlayer->play();
        return;
    }

}

void MainWindow::on_pushButtonDeleteCaption_clicked()
{
    captionName.clear();
    captionPath.clear();
    labelCaption->setText("当前载入的字幕文件名：");
}


void MainWindow::on_pushButtonDeleteObject_clicked()
{
    if(chosenNum == 0)
    {
        return;
    }
    for(int i = timeList.size() - 1; i >= 0; i--)
    {
        if(chosen[i] == 1)
        {
            timeList[i]->hide();
            timeList.removeAt(i);
            continue;
        }
    }
    setTimeList();

}


//设置时间轴对象的参数
void MainWindow::on_pushButtonSet_clicked()
{
    if(chosenNum != 1)
    {
        return;
    }

    int chosenOne = -1;
    for(int i = 0; i < timeList.size(); i++)
    {
        if(chosen[i] == 1)
        {
            chosenOne = i;
            break;
        }
    }
    if(timeList[chosenOne]->getType() == 0)
    {
        return;
    }
    if(timeList[chosenOne]->getType() == 1)
    {
        imageSetDialog *dlg = new imageSetDialog(this);
        dlg->showStartEnd(timeList[chosenOne]->getStart(), timeList[chosenOne]->getDuration());
        dlg->showXY(timeList[chosenOne]->getX(), timeList[chosenOne]->getY());

        dlg->showEffectId(timeList[chosenOne]->getEffectId());
        if(dlg->exec() == QDialog::Accepted)
        {
            timeList[chosenOne]->setX(dlg->getX());
            timeList[chosenOne]->setY(dlg->getY());
            timeList[chosenOne]->setStart(dlg->getStart());
            timeList[chosenOne]->setDuration(dlg->getDuration());

            timeList[chosenOne]->setEffectId(dlg->getEffectId());
            setTimeList();
            return;
        }
    }
    if(timeList[chosenOne]->getType() == 2)
    {
        textSetDialog *dlg = new textSetDialog(this);
        dlg->showStartEnd(timeList[chosenOne]->getStart(), timeList[chosenOne]->getDuration());
        dlg->showXY(timeList[chosenOne]->getX(), timeList[chosenOne]->getY());

        if(dlg->exec() == QDialog::Accepted)
        {
            timeList[chosenOne]->setX(dlg->getX());
            timeList[chosenOne]->setY(dlg->getY());
            timeList[chosenOne]->setStart(dlg->getStart());
            timeList[chosenOne]->setDuration(dlg->getDuration());
            setTimeList();
            return;

        }
    }
}


void MainWindow::on_pushButtonUp_clicked()
{
    if(chosenNum != 1)
    {
        return;
    }
    int chosenOne = -1;
    for(int i = 0; i < timeList.size(); i++)
    {
        if(chosen[i] == 1)
        {
            chosenOne = i;
            break;
        }
    }
    if(chosenOne == 0)
    {
        return;
    }
    timeList.swapItemsAt(chosenOne, chosenOne - 1);
    setTimeList();

}


void MainWindow::on_pushButtonDown_clicked()
{
    if(chosenNum != 1)
    {
        return;
    }
    int chosenOne = -1;
    for(int i = 0; i < timeList.size(); i++)
    {
        if(chosen[i] == 1)
        {
            chosenOne = i;
            break;
        }
    }
    if(chosenOne == timeList.size() - 1)
    {
        return;
    }
    timeList.swapItemsAt(chosenOne, chosenOne + 1);
    setTimeList();

}

//视频裁剪
void MainWindow::on_pushButtonCut_clicked()
{
    if(chosenNum != 1)
    {
        return;
    }
    int chosenOne = -1;
    for(int i = 0; i < timeList.size(); i++)
    {
        if(chosen[i] == 1)
        {
            chosenOne = i;
            break;
        }
    }
    if(timeList[chosenOne]->getType() != 0)
    {
        return;
    }
    videoCutDialog *dlg = new videoCutDialog(this);
    dlg->showDuration(timeList[chosenOne]->getDuration());
    if(dlg->exec() == QDialog::Accepted)
    {
        int newStart = dlg->getNewStart();
        int newDuration = dlg->getNewDuration();
        if(newStart + newDuration >= timeList[chosenOne]->getDuration())
        {
            QMessageBox::information(this, "提示", "设置的时间不合法！");
            return;
        }

        QString start;
        start.setNum(newStart);
        QString dur;
        dur.setNum(newDuration);

        QString name = QFileInfo(timeList[chosenOne]->getFileName()).baseName();

        QString suffix = QFileInfo(timeList[chosenOne]->getFileName()).suffix();

        QDateTime current = QDateTime::currentDateTime();

        QString currentDateTime = current.toString("-yy-MM-dd-hh-mm-ss-zzz");

        name += currentDateTime + "." + suffix;

        QString newPath = currentDir + "/temp/" + name;

        QString path = timeList[chosenOne]->getFilePath();

        QStringList arg;

        arg << "-ss" << start << "-t" << dur
            << "-i" << path
            << "-codec" << "copy"
            << newPath;

        QProcess::execute(program, arg);

        timeList[chosenOne]->hide();
        timeList[chosenOne]->setDuration(newDuration);
        timeList[chosenOne]->setFileName(name);
        timeList[chosenOne]->setFilePath(newPath);

        setTimeList();


        QListWidgetItem *it = new QListWidgetItem(QIcon(":/icon/icon/video.png"), name, ui->listWidgetVideo);

        //添加到视频列表
        it->setFlags(it->flags()|Qt::ItemIsEditable);
        ui->listWidgetVideo->addItem(it);
        videoList.insert(newPath, name);
        videoNameList.append(name);
    }


}



//视频切分
void MainWindow::on_pushButtonDivide_clicked()
{
    if(chosenNum != 1)
    {
        return;
    }
    int chosenOne = -1;
    for(int i = 0; i < timeList.size(); i++)
    {
        if(chosen[i] == 1)
        {
            chosenOne = i;
            break;
        }
    }
    if(timeList[chosenOne]->getType() != 0)
    {
        return;
    }
    if(timeList[chosenOne]->getDuration() == 1)
    {
        QMessageBox::information(this, "提示", "视频时长需要大于1秒！");
        return;
    }
    videoDivideDialog *dlg = new videoDivideDialog(this);
    dlg->showDuration(timeList[chosenOne]->getDuration());

    if(dlg->exec() == QDialog::Accepted)
    {
        int dur1 = dlg->getTime();

        int start1 = timeList[chosenOne]->getStart();

        int dur2 = timeList[chosenOne]->getDuration() - dur1;
        int start2 = start1 + dur1; //第二个视频在时间轴的开始时间

        QString d1;
        d1.setNum(dur1);

        QString d2;
        d2.setNum(dur2);

        QString name = QFileInfo(timeList[chosenOne]->getFileName()).baseName();
        QString suffix = QFileInfo(timeList[chosenOne]->getFileName()).suffix();


        QDateTime current1 = QDateTime::currentDateTime();


        QString currentDateTime1 = current1.toString("-yy-MM-dd-hh-mm-ss-zzz");

        QString name1 = name;

        name1 += currentDateTime1 + "." + suffix;

        QString newPath1 = currentDir + "/temp/" + name1;

        QString path = timeList[chosenOne]->getFilePath();

        QStringList arg1;

        //生成第一段视频
        arg1 << "-ss" << "0" << "-t" << d1
             << "-i" << path
             << "-codec" << "copy"
             << newPath1;

        QProcess::execute(program, arg1);

        QStringList arg2;

        QDateTime current2 = QDateTime::currentDateTime();

        current2 = current2.addMSecs(1);

        QString currentDateTime2 = current2.toString("-yy-MM-dd-hh-mm-ss-zzz");

        QString name2 = name;

        name2 += currentDateTime2 + "." + suffix;

        QString newPath2 = currentDir + "/temp/" + name2;

        //生成第二段视频
        arg2 << "-ss" << d1 << "-t" << d2
             << "-i" << path
             << "-codec" << "copy"
             << newPath2;

        QProcess::execute(program, arg2);


        QListWidgetItem *it1 = new QListWidgetItem(QIcon(":/icon/icon/video.png"), name1, ui->listWidgetVideo);

        //添加到视频列表
        it1->setFlags(it1->flags()|Qt::ItemIsEditable);
        ui->listWidgetVideo->addItem(it1);
        videoList.insert(newPath1, name1);
        videoNameList.append(name1);

        QListWidgetItem *it2 = new QListWidgetItem(QIcon(":/icon/icon/video.png"), name2, ui->listWidgetVideo);

        //添加到视频列表
        it2->setFlags(it2->flags()|Qt::ItemIsEditable);
        ui->listWidgetVideo->addItem(it2);
        videoList.insert(newPath2, name2);
        videoNameList.append(name2);


        timeLineWidget *timelinewidget1 = new timeLineWidget(0, name1, newPath1, start1, dur1, ui->timeLineContent);

        timeLineWidget *timelinewidget2 = new timeLineWidget(0, name2, newPath2, start2, dur2, ui->timeLineContent);

        timeList[chosenOne]->hide(); //先hide才能去除颜色，否则颜色会留在那
        timeList.removeAt(chosenOne);
        timeList.insert(chosenOne, timelinewidget2);
        timeList.insert(chosenOne, timelinewidget1);

        chosen.append(0);
        setTimeList();

    }

}

//视频合并
void MainWindow::on_pushButtonConcat_clicked()
{
    if(chosenNum <= 1)
    {
        return;
    }
    if(chosenNum >= 3)
    {
        QMessageBox::information(this, "提示", "仅能将2个视频对象合并！");
        return;
    }
    int chosen1 = -1;
    int chosen2 = -1;
    for(int i = 0; i < timeList.size(); i++)
    {
        if(chosen[i] == 1)
        {
            chosen1 = i;
            break;
        }
    }
    for(int i = chosen1 + 1; i < timeList.size(); i++)
    {
        if(chosen[i] == 1)
        {
            chosen2 = i;
            break;
        }
    }
    if(!(timeList[chosen1]->getType() == 0 && timeList[chosen2]->getType() == 0))
    {
        QMessageBox::information(this, "提示", "仅能将视频进行合并！");
        return;
    }

    //默认chosen1在前，chosen2在后
    QString name1 = QFileInfo(timeList[chosen1]->getFileName()).baseName(); //文件1的原名
    QString name2 = QFileInfo(timeList[chosen2]->getFileName()).baseName(); //文件2的原名

    QString suffix1 = QFileInfo(timeList[chosen1]->getFileName()).suffix();
    QString suffix2 = QFileInfo(timeList[chosen2]->getFileName()).suffix();

    QString path1 = timeList[chosen1]->getFilePath();
    QString path2 = timeList[chosen2]->getFilePath();


    QDateTime current1 = QDateTime::currentDateTime();
    QString currentDateTime1 = current1.toString("-yy-MM-dd-hh-mm-ss-zzz");

    QString ts1 = name1;

    ts1.append(currentDateTime1);
    ts1.append(".ts");
    QString ts1Path = currentDir + "/temp/" + ts1;

    QStringList arg1;

    arg1 << "-i" << path1
         << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts"
         << ts1Path;

    QProcess::execute(program, arg1);


    QDateTime current2 = QDateTime::currentDateTime();
    current2 = current2.addMSecs(1);
    QString currentDateTime2 = current2.toString("-yy-MM-dd-hh-mm-ss-zzz");
    QString ts2 = name2;
    ts2.append(currentDateTime2);
    ts2.append(".ts");
    QString ts2Path = currentDir + "/temp/" + ts2;

    QStringList arg2;

    arg2 << "-i" << path2
         << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts"
         << ts2Path;

    QProcess::execute(program, arg2);

    QDateTime current3 = QDateTime::currentDateTime();
    current3 = current3.addMSecs(1);
    QString currentDateTime3 = current3.toString("-yy-MM-dd-hh-mm-ss-zzz");

    QString txtName = currentDateTime3 + ".txt";
    QString txtPath = currentDir + "/temp/" + txtName;

    //写入txt文件
    QFile file(txtPath);
    file.open(QIODevice::Append|QIODevice::Text);
    QTextStream stream(&file);
    stream << "file " << "\'" << ts1 << "\'" << "\n"
           << "file " << "\'" << ts2 << "\'" ;
    file.close();

    //2个视频合成
    QString newName = name1;

    newName += currentDateTime3 + "." + suffix1;

    QString newPath = currentDir + "/temp/" + newName;

    QStringList arg3;

    arg3 << "-f" << "concat"
         << "-i" << txtPath
         << "-c" << "copy"
         << newPath;

    QProcess::execute(program, arg3);

    int newStart = timeList[chosen1]->getStart();
    int newDuration = timeList[chosen1]->getDuration() + timeList[chosen2]->getDuration();

    timeLineWidget *timelinewidget = new timeLineWidget(0, newName, newPath, newStart, newDuration, ui->timeLineContent);
    timeList[chosen1]->hide();
    timeList[chosen2]->hide();
    timeList.removeAt(chosen2);
    timeList.removeAt(chosen1);

    timeList.insert(chosen1, timelinewidget);

    setTimeList();

    QListWidgetItem *it = new QListWidgetItem(QIcon(":/icon/icon/video.png"), newName, ui->listWidgetVideo);

    //添加到视频列表
    it->setFlags(it->flags()|Qt::ItemIsEditable);
    ui->listWidgetVideo->addItem(it);
    videoList.insert(newPath, newName);
    videoNameList.append(newName);

}





