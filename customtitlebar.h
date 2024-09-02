#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>

class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleBar(QWidget *parent = nullptr);

private slots:
    void onMinimizeClicked();
    void onMaximizeClicked();
    void onCloseClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel *titleLabel;
    QPushButton *minimizeButton;
    QPushButton *maximizeButton;
    QPushButton *closeButton;
    QPoint windowPos;
    QPoint mousePos;
    bool mousePressed;

    void setButtonStyle(QPushButton *button);
};

#endif // CUSTOMTITLEBAR_H
