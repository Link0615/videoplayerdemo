#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QVideoWidget>

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = nullptr);

    QVideoWidget* videoWidget() const;
    QMediaPlayer* mediaPlayer() const;  // 提供访问 QMediaPlayer 的接口
    void play(const QString &filePath);
    void setPlaybackRate(float rate);
    void setPosition(int position);

signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);

private:
    QMediaPlayer *m_mediaPlayer;
    QVideoWidget *m_videoWidget;
};

#endif // VIDEOPLAYER_H
