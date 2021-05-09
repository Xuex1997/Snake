#include "widget.h"
#include "mainwindow.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(GAME_AREA_WIDTH, GAME_AREA_HIGHT);
    this->setWindowTitle("贪吃蛇");

    startPush=new QPushButton(this);
    startPush->setIcon(QIcon(":img/start"));
    startPush->setIconSize(QSize(920,45));
    startPush->setGeometry(500,500, 90, 45);
    startPush->setFlat(1);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/background").scaled(this->size())));
    this->setPalette(palette);
    connect(startPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
}

Widget::~Widget()
{

}

void Widget::M_startPush()
{
    gamewindow=new MainWindow(this);  //创建一个新的界面，任然以原来的界面为父窗口，退出后可以直接回到上一个界面。
    gamewindow->show();
}
