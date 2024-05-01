#include "sun.h"
#include <QDebug>

//随机位置掉落
Sun::Sun()
{
    //设置随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//================================================================
    //加载图片
//    dest = QPointF(((qrand() % 715 + 40) * 191 ) % 715 + 40, 90);
    dest = QPointF(((qrand() % 715 + 40) * 191 ) % 715 + 40, 130 + qrand() % (98 * 5));
    setPos(QPointF(dest.x(), 70));
    speed = 60.0 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/new/prefix1/imag/sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);

//    QImage img(":/new/prefix1/imag/AIIT.png");
//    this->setPixmap(QPixmap::fromImage(img));
//    this->resize(img.width(), img.height());

//=============================================================
}
//在具体位置生成
Sun::Sun(QPointF pos)
{
    dest = QPointF(pos.x() + qrand() % 30 - 15, pos.y() + qrand() % 30 + 15);
    setPos(QPointF(dest.x(), pos.y()));
    speed = 60 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/new/prefix1/imag/sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

Sun::~Sun(){
    delete movie;
}

QRectF Sun::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}

//鼠标点击拾取阳光
void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);
    shop->sun += 25;
    counter = time;
    event->setAccepted(true);
}

void Sun::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (++counter >= time)
        delete this;
    else if (y() < dest.y())
        setY(y() + speed);
}
//void Sun::run()//天空掉落的阳光
//{
//    //x(40 ~ 755)  y(285 ~ 575)
//    int x = ((qrand() % 715 + 40) * 191 ) % 715 + 40;
//    this->move(x,90);//阳光产生的起始位置
//    this->show();
//    m_animation = new QPropertyAnimation();
//    m_animation->setTargetObject(this);    //设置使用动画的控件
//    m_animation->setEasingCurve(QEasingCurve::Linear);

//    m_animation->setPropertyName("pos");
//    m_animation->setDuration(4 * 1000);//落下大概4秒
//    m_animation->setStartValue(this->pos());
//    int y = (((qrand() % 190) + 285) * 191 ) % 190 + 285;
//    m_animation->setEndValue(QPoint(this->pos().x(), y));//阳光落地位置
//    m_animation->start();
//}

//void Sun::run(int row, int col)//植物掉落的阳光
//{
//    int x = sun_point[row][col].first, y = sun_point[row][col].second;
//    this->move(x,y);//阳光产生的起始位置
//    this->show();
//}


//bool Sun::event(QEvent *event)
//{
//    if (event->type() == QEvent::MouseButtonPress)//捡到了阳光！
//    {
//        get_sun_sound();
//        //到时候这里要发送一个捡起了阳光的信号，最好带个加多少阳光的参数
//        emit get_sun(25);
//        this->close();
//    }

//    return QLabel::event(event);
//}
