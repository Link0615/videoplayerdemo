#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "videoplayer.h"
#include "customtitlebar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addVideoButton_clicked();
    void on_removeVideoButton_clicked();
    void on_moveUpButton_clicked();
    void on_moveDownButton_clicked();
    void on_speedComboBox_currentIndexChanged(int index);
    void on_videoListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_videoSlider_sliderMoved(int position);
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
    VideoPlayer *player; // 用于处理视频播放的自定义类
};

#endif // MAINWINDOW_H
