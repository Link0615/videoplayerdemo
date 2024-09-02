#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent) : QObject(parent)
{
    m_mediaPlayer = new QMediaPlayer(this);
    m_videoWidget = new QVideoWidget;

    m_mediaPlayer->setVideoOutput(m_videoWidget);

    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
}

QVideoWidget* VideoPlayer::videoWidget() const
{
    return m_videoWidget;
}

QMediaPlayer* VideoPlayer::mediaPlayer() const
{
    return m_mediaPlayer;
}

void VideoPlayer::play(const QString &filePath)
{
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(filePath));
    m_mediaPlayer->play();
}

void VideoPlayer::setPlaybackRate(float rate)
{
    m_mediaPlayer->setPlaybackRate(rate);
}

void VideoPlayer::setPosition(int position)
{
    m_mediaPlayer->setPosition(position);
}
