#ifndef MUSIC_H
#define MUSIC_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>

class Music
{
public:
    Music(QString url);
    Music();
    void play();
    void stop();
    void pause();
    void setmusic(QString url);
    QString music_url;
    void my_continue();
private:

};

#endif // MUSIC_H
