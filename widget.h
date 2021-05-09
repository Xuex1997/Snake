#ifndef WIDGET_H
#define WIDGET_H

#include<QWidget>
#include<QIcon>
#include<QPalette>
#include<QBrush>
#include<QPixmap>
#include<QPushButton>
#include<QMessageBox>

#include"mainwindow.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QPushButton *startPush;
    MainWindow  *gamewindow;//声明一个新的界面

private slots:
    void M_startPush();

};


#endif // WIDGET_H
