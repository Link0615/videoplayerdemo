#include "customtitlebar.h"
#include <QApplication>
#include <QMouseEvent>

CustomTitleBar::CustomTitleBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(40); // 设置标题栏的高度为40像素
    this->setStyleSheet("background-color: red; color: white;");

    titleLabel = new QLabel("视频播放器", this);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    minimizeButton = new QPushButton("-", this);
    maximizeButton = new QPushButton("□", this);
    closeButton = new QPushButton("×", this);

    // 设置布局
    QHBoxLayout *titleLayout = new QHBoxLayout(this);
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(minimizeButton);
    titleLayout->addWidget(maximizeButton);
    titleLayout->addWidget(closeButton);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(0); // 去除按钮之间的空隙
    this->setLayout(titleLayout);

    // 信号和槽的连接
    connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::onMinimizeClicked);
    connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::onMaximizeClicked);
    connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::onCloseClicked);
}


void CustomTitleBar::setButtonStyle(QPushButton *button)
{
    button->setFlat(true);
    button->setFixedSize(40, 30);  // 与谷歌浏览器相似的按钮尺寸
    button->setStyleSheet("QPushButton { border: none; background-color: transparent; font-size: 16px; color: white; }"
                          "QPushButton:hover { background-color: #555555; }"
                          "QPushButton:pressed { background-color: #777777; }");
}

void CustomTitleBar::onMinimizeClicked()
{
    window()->showMinimized();
}

void CustomTitleBar::onMaximizeClicked()
{
    if (window()->isMaximized())
        window()->showNormal();
    else
        window()->showMaximized();
}

void CustomTitleBar::onCloseClicked()
{
    window()->close();
}

void CustomTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePos = event->globalPos();
        windowPos = this->window()->frameGeometry().topLeft();
    }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed) {
        QPoint delta = event->globalPos() - mousePos;
        this->window()->move(windowPos + delta);
    }
}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mousePressed = false;
}
