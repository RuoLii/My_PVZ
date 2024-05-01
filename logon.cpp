#include "logon.h"
#include "ui_logon.h"

Logon::Logon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logon)
{
    ui->setupUi(this);
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/logon.png");
    img = img.scaled(this->size());
    pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

    for(int i = 0; i < N; i ++ )
        clickedrow[i] = false;

    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightblue;}");
    //设置选中背景色
    ui->tableWidget->setStyleSheet("selection-background-color:rgb(20,180,15);");
    //创建一个user
    ui->tableWidget->setRowCount(3);//游戏中默认拥有三个游戏账户
    string user[3] = {"温和的豌豆射手", "勇敢的坚果墙", "暴躁的土豆地雷"};
    for(int i = 0; i < 3; i ++ )
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(user[i])));


    //设置所有单元格不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //把封装好的自定义按钮根据绝对坐标放到窗口上

    //创建renamebutton

    renamebutton = new Logonbutton(QString(":/new/prefix1/imag/RenameButton_1.png"), QString(":/new/prefix1/imag/RenameButton_2.png"));
    renamebutton->setParent(this);
    renamebutton->move(36,366);
        //设置renamebutton按钮被按压时的信号连接
    connect(renamebutton, &Logonbutton::pressed,[=](){
        renamebutton->move1(1);
        //播放一次gravebutton.wav
        renamebutton->sound1();
    });
        //同理设置释放按钮时的信号连接
    connect(renamebutton, &Logonbutton::released,[=](){
       renamebutton->move2(1);
    });

    //创建okbutton
    okbutton = new Logonbutton(QString(":/new/prefix1/imag/Okbutton_1.png"),QString(":/new/prefix1/imag/Okbutton_2.png"));
    okbutton->setParent(this);
    okbutton->move(36,410);
    connect(okbutton, &Logonbutton::pressed,[=](){
        okbutton->move1(1);
        okbutton->sound1();
    });
    connect(okbutton, &Logonbutton::released,[=](){
       okbutton->move2(1);
    });
    //创建deletebutton
    deletebutton = new Logonbutton(QString(":/new/prefix1/imag/Deletebutton_1.png"),QString(":/new/prefix1/imag/Deletebutton_2.png"));
    deletebutton->setParent(this);
    deletebutton->move(297,366);
    connect(deletebutton, &Logonbutton::pressed,[=](){
        deletebutton->move1(1);
        deletebutton->sound1();
    });
    connect(deletebutton, &Logonbutton::released,[=](){
       deletebutton->move2(1);
    });
    //创建cancelbutton
    cancelbutton = new Logonbutton(QString(":/new/prefix1/imag/Cancelbutton_1.png"),QString(":/new/prefix1/imag/Cancelbutton_2.png"));
    cancelbutton->setParent(this);
    cancelbutton->move(297,410);
    connect(cancelbutton, &Logonbutton::pressed,[=](){
        cancelbutton->move1(1);
        cancelbutton->sound1();
    });
    connect(cancelbutton, &Logonbutton::released,[=](){
       cancelbutton->move2(1);
    });


    //当点击tablewidget内的单元格时，发送一个已点击的信号,还可以来一个点击音效，增加用户交互性
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(show_prodcut_sets(int,int)));//连接删除的方法

    //rename
    //实现效果：
    /*
     添加新用户
     */
    connect(renamebutton, &QPushButton::released, [=](){
        int idx = -1;
        for(int i = 0; i < N; i ++ ){
            if (clickedrow[i] == true) {
                idx = i;
                break;
            }
        }
        if (idx == -1){
            QMessageBox::warning(this, "警告", "您没有选择任一用户！\n请选择用户后重试！");
        }else{
            //这里后续写rename的操作代码





        }
    });
    //ok(已完成)
    //实现效果：
    /*
      点击一个单元格内的user会传入数据
      此时点击ok会将新点击的一行的user数据传给主界面
      并且关闭logon界面
      */
    connect(okbutton, &QPushButton::released, [=](){
        int idx = -1;
        for(int i = 0; i < N; i ++ ){
            if(clickedrow[i] == true){
                idx = i;
                break;
            }
        }
        if (idx == -1){
            QMessageBox::warning(this, "警告", "您没有选择任一用户！\n请选择用户进行登录！");
        }else{
            //加载这个user的游戏记录

            //发送一个用户已经选择User的信号（给mainwi用）
            emit Complete_user_selection(idx);

            old_user = idx;

            this->hide();
        }
    });
    //delete
    //实现效果：
    /*
       选择一个用户进行删除
      */
    connect(deletebutton, &QPushButton::released,[=](){
        int idx = -1;
        for(int i = 0; i < N; i ++ ){
            if(clickedrow[i] == true){
                idx = i;
                break;
            }
        }
        if (idx == -1){
            QMessageBox::warning(this, "警告", "您没有选择任一用户！\n请选择用户后再进行删除！");
        }else{
            qDebug() << "delete!!" << idx;
            //再次提问用户是否删除这个User
            QString deluser = "您正在删除: " + QString::number(idx) + "\n请问您要继续吗？";
            int op = QMessageBox::question(this, "敏感操作",deluser, QMessageBox::Ok, QMessageBox::Cancel);
            if (op == QMessageBox::Ok){
                qDebug() << "已删除User！";

                //这里后续写删除文件流的操作


                QMessageBox::information(this, "提示", "删除成功！");
                //重新刷新一下用户列表


            }
        }
    });
    //cancel(已完成)
    //实现效果：
    /*
     取消，返回
     当用户选择了一个user进行登录后，重新打开logon界面
     无论重新选择了哪一个user，只要点击了cancel关闭，就维持old_user的登录状态
     */
    connect(cancelbutton,&QPushButton::released, [=](){
        int idx = -1;
        for(int i = 0; i < N; i ++ ){
            if(clickedrow[i] == true){
                idx = i;
                break;
            }
        }
        //第一次登录：不选择就弹窗警告
        //登录后再次选择：不选择->关闭
        //              选择->关闭
        if (old_user == -1){
            QMessageBox::warning(this, "警告", "您没有选择任一用户！\n请登录后重试！");
        }else{
            qDebug() << "cancel!!" << old_user;
            emit Complete_user_selection(old_user);

            this->hide();
        }
    });

    startSound = new QMediaPlayer(this);





}

Logon::~Logon()
{
    delete ui;
    delete pic;
    delete renamebutton;
    delete okbutton;
    delete deletebutton;
    delete cancelbutton;
    delete startSound;
}

void Logon::show_prodcut_sets(int row, int col)
{
    Q_UNUSED(col);
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/tap2.mp3"));  //将音乐文件添加到播放列表中
    startSound->play();
    if(old != -1) clickedrow[old] = false;
    old = row;
    clickedrow[row] = true;//第row行的user数据被点击了
}
