#include "music.h"

bool is_play = false;
QMediaPlayer startSound;
QMediaPlaylist startList;

Music::Music(QString url)
{
    music_url = url;
}

Music::Music()
{

}

void Music::play()
{
    //设置背景音乐
    // 创建媒体播放器和媒体播放列表
    if (is_play == true)
        startSound.stop();
    if(music_url == "null"){
        startSound.stop();
        return;
    }
    startList.clear();
    startList.setPlaybackMode((QMediaPlaylist::Loop));  //设置播放模式为循环播放
    startList.addMedia(QUrl(music_url));  //将音乐文件添加到播放列表中
    startSound.setPlaylist(&startList);  // 将音乐文件添加到播放列表中
    startSound.setVolume(80);  //设置音量
    startSound.play();
    is_play = true;
}

void Music::stop()
{
    startSound.stop();
}

void Music::pause()
{
    startSound.pause();
}

void Music::setmusic(QString url)
{
    music_url = url;
}

void Music::my_continue(){
    startSound.play();
}
