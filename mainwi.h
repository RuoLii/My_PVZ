#ifndef MAINWI_H
#define MAINWI_H

#include <QWidget>
#include <music.h>
#include <logon.h>
#include <seedbank.h>
#include <day.h>
#include <whackgame.h>
#include <sokoban.h>
#include <wisdom_tree.h>
#include <wanttosay.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWi; }
QT_END_NAMESPACE


class MainWi : public QWidget
{
    Q_OBJECT

public:
    MainWi(bool state = false, QWidget *parent = nullptr);
    ~MainWi();
    void showAll();

public:
    int user_idx = -1;
private:
    Ui::MainWi *ui;
    QBrush *pic;
    Logon *logon;
    Logonbutton *huchulogonbutton;
    Logonbutton *startbutton;
    Logonbutton *mini_gamesbutton;
    Logonbutton *puzzlebutton;
    Logonbutton *survivalbutton;
    Logonbutton *optionsbutton;
    Logonbutton *helpbutton;
    Logonbutton *quitbutton;
    Seedbank seedbank;

private slots:
    void showAllbutton_slot(int idx);

};
#endif // MAINWI_H
