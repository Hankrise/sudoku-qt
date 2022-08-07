#include "form.h"
#include "ui_form.h"
#include<QPushButton>
#include"widget.h"
#include<QSize>
#define cout qDebug().noquote().nospace()

Form::Form(QPoint point,QWidget *parent,Widget* widget,int r,int c) :
    QDialog(parent),_widget(widget),_r(r),_c(c),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    //假设四个参数是x，y，a，b，从x，y这个位置开始打开一个a * b大小的窗口
    this->setGeometry(point.x(),point.y(),this->width(),this->height());
    //但是如果一move的话还是从0，0开始move
    this->move(point.x()+65,point.y()-this->height()/2);
    QIcon _icon[9];
    //设置好9个图标Icon
    _icon[0].addFile(QString::fromUtf8(":/image/1.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[1].addFile(QString::fromUtf8(":/image/2.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[2].addFile(QString::fromUtf8(":/image/3.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[3].addFile(QString::fromUtf8(":/image/4.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[4].addFile(QString::fromUtf8(":/image/5.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[5].addFile(QString::fromUtf8(":/image/6.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[6].addFile(QString::fromUtf8(":/image/7.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[7].addFile(QString::fromUtf8(":/image/8.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
    _icon[8].addFile(QString::fromUtf8(":/image/9.png"), QSize(50,50), QIcon::Normal, QIcon::Off);


    for(int i=0;i<9;i++)//设置好9个按钮
    {
        _btn[i].setFixedSize(45,45);
        _btn[i].setStyleSheet("color:blue");
        _btn[i].setIcon(_icon[i]);
        _btn[i].setIconSize(QSize(45,45));
        QFont font(nullptr,25);
        _btn[i].setFont(font);
        //_btn[i].setText(QString::number(i+1));
        ui->gridLayout->addWidget(&_btn[i],i/3,i%3);
        connect(&_btn[i],&QPushButton::clicked,[=](){//点击按钮就设置为对应的数字
            _widget->setNum(_r,_c,i+1);
            this->close();
        });
    }
    connect(ui->btn_clear,&QPushButton::clicked,this,&Form::clearNumWhenClicked);//点击清除当前方格就清除数字
}

Form::~Form()
{
    delete ui;
}

void Form::clearNumWhenClicked()
{
    _widget->clearNum(_r,_c);
    this->close();
}
