QT       += core gui multimedia multimediawidgets
RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imagedurationdialog.cpp \
    imagesetdialog.cpp \
    instructdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    textdialog.cpp \
    textdurationdialog.cpp \
    textsetdialog.cpp \
    timeline.cpp \
    timelinewidget.cpp \
    videocutdialog.cpp \
    videodividedialog.cpp

HEADERS += \
    imagedurationdialog.h \
    imagesetdialog.h \
    instructdialog.h \
    mainwindow.h \
    textdialog.h \
    textdurationdialog.h \
    textsetdialog.h \
    timeline.h \
    timelinewidget.h \
    videocutdialog.h \
    videodividedialog.h

FORMS += \
    imagedurationdialog.ui \
    imagesetdialog.ui \
    instructdialog.ui \
    mainwindow.ui \
    textdialog.ui \
    textdurationdialog.ui \
    textsetdialog.ui \
    videocutdialog.ui \
    videodividedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
