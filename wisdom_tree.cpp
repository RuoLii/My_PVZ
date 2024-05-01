#include "wisdom_tree.h"
#include "ui_wisdom_tree.h"

Wisdom_tree::Wisdom_tree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wisdom_tree)
{
    ui->setupUi(this);
    ui->answer->hide();
    ui->textEdit->clear();
    ui->textEdit->hide();
//设置背景图片========================================
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/tree_of_wisdom.png");
    img = img.scaled(this->size());
    pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

//创建返回主页面按钮==================================
    back_main_menubutton = new Logonbutton(QString(":/new/prefix1/imag/tree_main_button_1.png"), QString(":/new/prefix1/imag/tree_main_button_2.png"));
    back_main_menubutton->setParent(this);
    back_main_menubutton->move(630,0);
    connect(back_main_menubutton, &Logonbutton::pressed,[=](){
        back_main_menubutton->move1(1);
        back_main_menubutton->sound1();
    });
    connect(back_main_menubutton, &Logonbutton::released,[=](){
       back_main_menubutton->move2(1);
       this->close();
       Music music("qrc:/new/prefix1/music/MainJM.mp3");
       music.play();
    });

    QPixmap map;
    map.load(":/new/prefix1/imag/TreeFood.png");
    ui->pushButton->setFixedSize(map.width(), map.height());
    ui->pushButton->setStyleSheet("QPushButton{border:0px;}");
    ui->pushButton->setIcon(map);
    ui->pushButton->setIconSize(QSize(map.width(),map.height()));

    //音乐播放
    Music music("qrc:/new/prefix1/music/flowery.mp3");
    music.play();

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

Wisdom_tree::~Wisdom_tree()
{
    delete ui;
    delete pic;
    delete back_main_menubutton;
}

void Wisdom_tree::on_pushButton_clicked()
{
    ui->textEdit->show();
    ui->answer->show();
    ui->textEdit->clear();
    QProcess myProcess;
    //相对路径用不来TOT
//    QString program = ":/new/prefix1/SparkCmd/demo/x64/Release/demo.exe";
    QString program = "C:\\Users\\RuoLi\\Desktop\\SparkCmd\\demo\\x64\\Release\\demo.exe";
//    QString program = "D:\\QT_cunchu\\My_PVZ\\SparkCmd\\demo\\x64\\Release\\demo.exe";

    //随机回答
    int t = qrand() % 6;
    QString s;
    switch(t){
    case 0:
        s = "请用50字简要描述一下植物大战僵尸中，寒冰射手的作用";break;
    case 1:
        s = "请用50字简要描述一下植物大战僵尸中，土豆地雷的作用";break;
    case 2:
        s = "请用50字简要描述一下植物大战僵尸中，坚果墙的作用";break;
    case 3:
        s = "请用50字简要描述一下植物大战僵尸中，橄榄球僵尸的特点";break;
    case 4:
        s = "用50字写植物大战僵尸游戏攻略";break;
    case 5:
        s = "从现在开始你是一棵智慧树，请你用50字向我普及一点植物大战僵尸小技巧";break;
    }

    QStringList args;
    args.append(s);
//    arguments<<args;//传递到exe的参数
    myProcess.start(program,args);
    while (myProcess.waitForFinished(100) == false) {
        QApplication::processEvents();
        QByteArray qByteRead = myProcess.readAllStandardOutput();
        if (!qByteRead.isEmpty()) {
            ui->textEdit->append(QString::fromLocal8Bit(qByteRead));
            repaint();
        }
    }
    QByteArray qByteRead = myProcess.readAllStandardOutput();
    ui->textEdit->append(QString::fromLocal8Bit(qByteRead));
}
