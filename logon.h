#ifndef LOGON_H
#define LOGON_H

#include <QWidget>
#include <iostream>
#include <logonbutton.h>
#include <QMessageBox>

using namespace std;

const int N = 10;//最多存10个user数据

namespace Ui {
class Logon;
}

class Logon : public QWidget
{
    Q_OBJECT

public:
    explicit Logon(QWidget *parent = nullptr);
    ~Logon();
    bool clickedrow[10];
    int old = -1;//上次点击的单元格
    int old_user = -1;//上次登录的user

private slots:
    void show_prodcut_sets(int,int);

private:
    Ui::Logon *ui;
    QBrush *pic;
    Logonbutton *renamebutton;
    Logonbutton *okbutton;
    Logonbutton *deletebutton;
    Logonbutton *cancelbutton;
    QMediaPlayer *startSound;

signals:
    void cellClicked(int,int);
    void Complete_user_selection(int idx);

};

#endif // LOGON_H
