#ifndef WISDOM_TREE_H
#define WISDOM_TREE_H

#include <QWidget>
#include <logonbutton.h>
#include <mainwi.h>
#include <music.h>
#include <QProcess>
#include <QTime>

namespace Ui {
class Wisdom_tree;
}

class Wisdom_tree : public QWidget
{
    Q_OBJECT

public:
    explicit Wisdom_tree(QWidget *parent = nullptr);
    ~Wisdom_tree();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Wisdom_tree *ui;
    QBrush *pic;
    Logonbutton *back_main_menubutton;
};

#endif // WISDOM_TREE_H
