#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <logon.h>
#include <mainwi.h>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;
    QBrush *pic;
    Logonbutton *back_to_gamebutton;
    Logonbutton *back_main_menubutton;

signals:
    void game();
    void mainwi();
};

#endif // MENU_H
