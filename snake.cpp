#include <qdebug.h>
#include "snake.h"

Snake::Snake()
{

}

Snake::~Snake()
{

}


Snake::Snake(QPoint head, QColor color):
    snakehead(head),snakecolor(color),snakeradius(INITAIL_RADIUS),snakescore(0), snakeskills(0), direction(0)
{
    for(int i=0;i<5;i++)
    {
        QPoint s(head.x(),head.y()+snakeradius+snakeradius*i);
        snakebody.push_back(s);
    }
}

void Snake::addbody(int adds)
{
    snakescore += adds;
    if(snakescore < 50) {
        QPoint p(snakebody[snakebody.size()-1].x(), snakebody[snakebody.size()-1].y());
        snakebody.push_back(p);
        return;
    }

    qreal r = INITAIL_RADIUS+((qreal)(snakescore-50))/25;
    snakeradius = r > MAX_RADIUS ? MAX_RADIUS : r;

    if(snakescore%50 == 0) {
        QPoint p(snakebody[snakebody.size()-1].x(), snakebody[snakebody.size()-1].y());
        snakebody.push_back(p);
    }
}

void Snake::snakeMove(int dir)
{
    for(int i=snakebody.size()-1; i>0; i--)
    {
        snakebody[i]=snakebody[i-1];
    }
    snakebody[0]=snakehead;

    //控制蛇的转弯角度
    int min_rot=(this->direction-MAX_ROTATE+360)%360;
    int max_rot=(this->direction+MAX_ROTATE)%360;
    if(min_rot < max_rot)
    {
        if(dir >= min_rot && dir <= max_rot)
            this->direction = dir;
        else if(dir>(this->direction+180)%360 || dir < min_rot)
        {
            this->direction = min_rot;
        } else
        {
            this->direction = max_rot;
        }
    }else{
        if(dir >= min_rot || dir <= max_rot)
            this->direction = dir;
        else if(dir>(this->direction+180)%360)
        {
            this->direction = min_rot;
        } else
        {
            this->direction = max_rot;
        }
    }

    int add_x = this->snakehead.x()+qRound(5*cos((qreal)this->direction/180 * PI));
    int add_y = this->snakehead.y()+qRound(5*sin((qreal)this->direction/180 * PI));

    this->setHead(QPoint(add_x,add_y));
}

QPoint Snake::getHead()
{
    return snakehead;
}
void Snake::setHead(QPoint p)
{
    snakehead = p;
}

QList<QPoint> Snake::getBody()
{
    return snakebody;
}

int Snake::getBodyLong()
{
    return snakebody.size();
}

QColor Snake::getColor()
{
    return snakecolor;
}

qreal Snake::getRadius()
{
    return snakeradius;
}

void Snake::setRadius(qreal radius) {
    this->snakeradius = radius;
}

void Snake::setDirection(int dir)
{
    this->direction = dir;
}
int Snake::getScore()
{
    return snakescore;
}

int Snake::getKill()
{
    return snakeskills;
}

void Snake::setKill(int k)
{
    snakeskills = k;
}
int Snake::move(int mouse_x, int mouse_y)
{
    int static lastx=0;
    int static lasty=0;

    //鼠标未移动
    if(lastx==mouse_x && lasty==mouse_y)
    {
        return this->direction;
    }

    //鼠标移动
    lastx=mouse_x;
    lasty=mouse_y;

    int headx=this->snakehead.x();
    int heady=this->snakehead.y();
    int dir = this->direction;

    if(mouse_x > headx && mouse_y >= heady)//第一象限X正半轴
    {
        dir = qRound(atan(((qreal)mouse_y-heady)/((qreal)mouse_x-headx))*180/PI);
    } else if(mouse_x <= headx && mouse_y > heady)
    {
        dir = qRound(atan((headx-(qreal)mouse_x)/((qreal)mouse_y-heady))*180/PI) + 90;
    } else if(mouse_x < headx && mouse_y <= heady)
    {
        dir = qRound(atan((heady-(qreal)mouse_y)/(headx-(qreal)mouse_x))*180/PI) + 180;
    } else if(mouse_x >= headx && mouse_y < heady)
    {
        dir = qRound(atan(((qreal)mouse_x-headx)/(heady-(qreal)mouse_y))*180/PI) + 270;
    }

    return dir;
}
