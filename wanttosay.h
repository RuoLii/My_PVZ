#ifndef WANTTOSAY_H
#define WANTTOSAY_H

#include <QWidget>
#include <music.h>
#include <logonbutton.h>

namespace Ui {
class WantToSay;
}

class WantToSay : public QWidget
{
    Q_OBJECT

public:
    explicit WantToSay(QWidget *parent = nullptr);
    ~WantToSay();

private:
    Ui::WantToSay *ui;
    QBrush *pic;
    Logonbutton *back_main_menubutton;
};

#endif // WANTTOSAY_H
