#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QVector>
#include <QColor>

#define INITAL_LENGTH 5
#define INITAIL_RADIUS 5
#define MAX_RADIUS 15
#define PI 3.141592653
#define MAX_ROTATE 60
class Snake
{
public:
    Snake();
    ~Snake();
    Snake(QPoint head, QColor color);

    QPoint getHead();
    void setHead(QPoint p);
    QList<QPoint> getBody();
    int getBodyLong();
    QColor getColor();
    qreal getRadius();
    void setRadius(qreal radius);
    void setDirection(int dir);
    int getScore();
    int getKill();
    void setKill(int k);

    void addbody(int adds);
    void snakeMove(int dir);
    int move(int mouse_x, int mouse_y);

private:
    QPoint snakehead;
    QList<QPoint> snakebody;
    QColor snakecolor;
    qreal snakeradius;
    int snakescore;
    int snakeskills;
    int direction;//表示蛇头的方向
};

#endif // SNAKE_H
