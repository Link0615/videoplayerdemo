QT       += core gui multimedia multimediawidgets
CONFIG   += c++17

SOURCES  += main.cpp \
            customtitlebar.cpp \
            mainwindow.cpp \
            videoplayer.cpp

HEADERS  += mainwindow.h \
            customtitlebar.h \
            videoplayer.h

FORMS    += mainwindow.ui

RESOURCES += \
    prefix.qrc
