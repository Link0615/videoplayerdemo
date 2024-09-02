#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

// 在MainWindow构造函数中
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new VideoPlayer(this))  // 初始化 VideoPlayer 对象
{
    ui->setupUi(this);

    // 隐藏默认的标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 创建自定义标题栏
    CustomTitleBar *titleBar = new CustomTitleBar(this);
    titleBar->setFixedHeight(40);  // 设置标题栏的高度

    // 创建一个新的 QWidget 作为容器，包含标题栏和主内容区
    QWidget *container = new QWidget(this);
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    containerLayout->setSpacing(0);  // 去除组件之间的空隙
    containerLayout->addWidget(titleBar);  // 添加标题栏
    containerLayout->addWidget(ui->centralwidget);  // 添加中央窗口内容
    container->setLayout(containerLayout);

    // 将这个容器设置为 MainWindow 的 central widget
    this->setCentralWidget(container);

    // 确保窗口可以缩小到一个合理的最小尺寸
    this->setMinimumSize(300, 200);  // 根据需要调整

    // 清空 verticalLayout_2 中的布局项
    QLayoutItem *item;
    while ((item = ui->verticalLayout_2->takeAt(0)) != nullptr) {
        delete item;
    }

    // 添加 QVideoWidget 到布局中
    ui->verticalLayout_2->addWidget(player->videoWidget());

    // 连接信号槽
    connect(ui->videoSlider, &QSlider::sliderMoved, player, &VideoPlayer::setPosition);
    connect(player, &VideoPlayer::positionChanged, ui->videoSlider, &QSlider::setValue);
    connect(player, &VideoPlayer::durationChanged, ui->videoSlider, &QSlider::setMaximum);

    ui->speedComboBox->addItems({"0.5x", "1x", "1.25x", "1.5x", "2x", "2.5x", "3x"});
    ui->speedComboBox->setCurrentIndex(1);  // 默认1x

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    player->videoWidget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // 连接列表项双击事件到播放函数
    connect(ui->videoListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::on_videoListWidget_itemDoubleClicked);
}


// 重写resizeEvent以确保标题栏在窗口大小变化时自动调整大小
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // 确保标题栏宽度随窗口大小变化
    CustomTitleBar *titleBar = findChild<CustomTitleBar *>();
    if (titleBar) {
        titleBar->setMinimumWidth(this->width());
        titleBar->resize(this->width(), titleBar->height());
    }
}


MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destructor called.";
    delete ui;
}

void MainWindow::on_addVideoButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "选择视频文件", QString(), "视频文件 (*.mp4 *.avi *.mkv)");
    foreach (QString file, files) {
        ui->videoListWidget->addItem(file);
    }
}

void MainWindow::on_removeVideoButton_clicked()
{
    delete ui->videoListWidget->currentItem();
}

void MainWindow::on_moveUpButton_clicked()
{
    int currentIndex = ui->videoListWidget->currentRow();
    if (currentIndex > 0) {
        QListWidgetItem *currentItem = ui->videoListWidget->takeItem(currentIndex);
        ui->videoListWidget->insertItem(currentIndex - 1, currentItem);
        ui->videoListWidget->setCurrentItem(currentItem);
    }
}

void MainWindow::on_moveDownButton_clicked()
{
    int currentIndex = ui->videoListWidget->currentRow();
    if (currentIndex < ui->videoListWidget->count() - 1) {
        QListWidgetItem *currentItem = ui->videoListWidget->takeItem(currentIndex);
        ui->videoListWidget->insertItem(currentIndex + 1, currentItem);
        ui->videoListWidget->setCurrentItem(currentItem);
    }
}

void MainWindow::on_speedComboBox_currentIndexChanged(int index)
{
    player->setPlaybackRate(ui->speedComboBox->itemText(index).remove("x").toFloat());
}

void MainWindow::on_videoListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    player->play(item->text());
}

void MainWindow::on_videoSlider_sliderMoved(int position)
{
    player->setPosition(position);
}
