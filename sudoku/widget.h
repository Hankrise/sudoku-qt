#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QMenu>
QT_BEGIN_NAMESPACE

namespace Ui { class Widget; }

QT_END_NAMESPACE
class Form;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void clearNum(int r,int c);//清除按钮上的数字
    void clearAllNum();
    void setNum(int r,int c,int num);//设置按钮上的数字
    void create(int cnt);//创建局面
    void chooseOne(int r,int c);//点击格子后触发此函数让玩家9选1
    bool check();//检查当前是否正确
    int get_num(int r,int c)//得到给定位置预设的数字
    {
        return _num[r][c];
    }
    void set_Num(int r,int c,int x)//设定给定位置预设的数字
    {
        _num[r][c]=x;
    }
private slots:
    void updateTimer();           // 计时//这里也是计时用
private:
    template<int n,int m>
    void shuffle(int (&mat)[n][m],int nShuffle=1);
private:
    Ui::Widget *ui;
    int _num[9][9];//预设的9*9数独
    QPushButton _btn[9][9];//9*9的按钮
    int timerSeconds;
    int cnt;
    QTimer *timer;     // 计时器//也是计时用
    QLabel *timeLabel; // 计时数字
    QIcon icon[18];
    int type=0;
    QString skin=QStringLiteral("blue");
};
/*
class mQMenu:public QMenu{
        Q_OBJECT
public:
    explicit mQMenu(QWidget *parent = nullptr);
    //自定义信号
    void mousePressEvent(QMouseEvent *);
signals:
    //信号没有返回值，可以有参数,信号函数不需要定义，只需要声明
    void menuclicked();

};
void mQMenu::mousePressEvent(QMouseEvent *){
    emit menuclicked();
}
*/
#endif // WIDGET_H
