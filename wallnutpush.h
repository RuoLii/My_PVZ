#ifndef WALLNUTPUSH_H
#define WALLNUTPUSH_H

#include <QLabel>
#include <QMovie>
#include <QDebug>

class WallnutPush : public QLabel
{
    Q_OBJECT
public:
    WallnutPush(int row, int col);
    ~WallnutPush();
    int row;
    int col;
private:
    QMovie *movie;

};

#endif // WALLNUTPUSH_H
