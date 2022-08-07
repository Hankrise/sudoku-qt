#include "widget.h"
#include "ui_widget.h"
#include"mypushbutton.h"
#include"form.h"
#include<QDebug>
#include<QPushButton>
#include<QColor>
#include<QString>
#include<QDialog>
#include<QAction>
#include<QMessageBox>
#include<QRandomGenerator>
#include<QString>
#include<QTimer>
#include<QTime>
#include<QMainWindow>
#include"highscore.h"
#include"scoreinput.h"
#define cout qDebug().noquote().nospace()
//我这里#define是为了调试方便

void Widget::chooseOne(int r,int c)
{
    QPoint point=this->cursor().pos();//获取鼠标位置
    Form* fm = new Form(point,0,this,r,c,skin);//新建一个9选1的
    fm->exec();
}

void Widget::create(int cnt)//随机生成一个一定有解的状态，cnt表示给玩家的数字的个数
{
    //我这里使用《编程之美》一书P97页左右的算法来生成数独，这本书上还有另一种更好的算法，不过比较麻烦，我就没用
    //而且这种算法能够生成9!种数独，够玩了


    QRandomGenerator rnd;
    rnd.seed(time(0));
    int mid[9]={0};
    bool use[9]={0};
    for(int i=0;i<9;i++)
    {
        bool flag=1;
        while(flag)
        {
            int tmp=(rnd()%9+9)%9;
            if(!use[tmp])
            {
                use[tmp]=1;
                mid[i]=tmp;
                flag=0;
            }
        }
    }
    int num[9][9]=
    {
        {mid[8],mid[6],mid[7],mid[2],mid[0],mid[1],mid[5],mid[3],mid[4]},
        {mid[2],mid[0],mid[1],mid[5],mid[3],mid[4],mid[8],mid[6],mid[7]},
        {mid[5],mid[3],mid[4],mid[8],mid[6],mid[7],mid[2],mid[0],mid[1]},
        {mid[6],mid[7],mid[8],mid[0],mid[1],mid[2],mid[3],mid[4],mid[5]},
        {mid[0],mid[1],mid[2],mid[3],mid[4],mid[5],mid[6],mid[7],mid[8]},
        {mid[3],mid[4],mid[5],mid[6],mid[7],mid[8],mid[0],mid[1],mid[2]},
        {mid[7],mid[8],mid[6],mid[1],mid[2],mid[0],mid[4],mid[5],mid[3]},
        {mid[1],mid[2],mid[0],mid[4],mid[5],mid[3],mid[7],mid[8],mid[6]},
        {mid[4],mid[5],mid[3],mid[7],mid[8],mid[6],mid[1],mid[2],mid[0]}
    };

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            num[i][j]++;
            set_Num(i,j,num[i][j]);//我们这里还有记好我们生成的数独，因为我们使用查看答案还是要用到的
        }
    }
    for(int i=0;i<9;i++)
            cout<<num[i][0]<<" "<<num[i][1]<<" "<<num[i][2]<<" "<<num[i][3]<<" "<<num[i][4]<<" "<<num[i][5]<<" "<<num[i][6]<<" "<<num[i][7]<<" "<<num[i][8];

    shuffle(num,10);//打乱
    for(int i=0;i<9;i++)for(int j=0;j<9;j++)set_Num(i,j,num[i][j]);//需要打乱后再set
    //调试代码
    for(int i=0;i<9;i++)
            cout<<num[i][0]<<" "<<num[i][1]<<" "<<num[i][2]<<" "<<num[i][3]<<" "<<num[i][4]<<" "<<num[i][5]<<" "<<num[i][6]<<" "<<num[i][7]<<" "<<num[i][8];
    bool s[81]={0};
    int count=0;
    //确定保留的数的位置
    while(count!=cnt)
    {
        int tmp=(rnd()%81+81)%81;
        if(s[tmp]==0) s[tmp]=1,count++;
    }

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            int tar=i*9+j;
            if(s[tar]==1)//对于要保留的数，我们让按钮失效
            {  // QFont font(nullptr,2);
                //_btn[i][j].setFont(font);
                //_btn[i][j].setText(QString::number(num[i][j]));
                if(num[i][j]==1)
                {   _btn[i][j].setFixedSize(41,41);
                    _btn[i][j].setIcon(icon[0]);
                    _btn[i][j].setIconSize(QSize(41,41));}

                if(num[i][j]==2)
                {   _btn[i][j].setFixedSize(41,41);
                    _btn[i][j].setIcon(icon[1]);
                    _btn[i][j].setIconSize(QSize(41,40));}

                if(num[i][j]==3)
                {   _btn[i][j].setFixedSize(41,41);
                    _btn[i][j].setIcon(icon[2]);
                    _btn[i][j].setIconSize(QSize(40,41));}

                if(num[i][j]==4)
                {   _btn[i][j].setFixedSize(41,41);
                    _btn[i][j].setIcon(icon[3]);
                    _btn[i][j].setIconSize(QSize(40,40));}

                if(num[i][j]==5)
                {   _btn[i][j].setFixedSize(40,40);
                    _btn[i][j].setIcon(icon[4]);
                    _btn[i][j].setIconSize(QSize(40,40));}

                if(num[i][j]==6)
                {   _btn[i][j].setFixedSize(40,40);
                    _btn[i][j].setIcon(icon[5]);
                    _btn[i][j].setIconSize(QSize(39,40));}

                if(num[i][j]==7)
                {   _btn[i][j].setFixedSize(40,40);
                    _btn[i][j].setIcon(icon[6]);
                    _btn[i][j].setIconSize(QSize(40,39));}

                if(num[i][j]==8)
                {   _btn[i][j].setFixedSize(40,40);
                    _btn[i][j].setIcon(icon[7]);
                    _btn[i][j].setIconSize(QSize(39,39));}

                if(num[i][j]==9)
                {   _btn[i][j].setFixedSize(39,39);
                    _btn[i][j].setIcon(icon[8]);
                    _btn[i][j].setIconSize(QSize(39,39));}

               // _btn[i][j].setStyleSheet("background-color:rgb(0,255,0)");
                _btn[i][j].setEnabled(false);
            }
        }
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("程序写的都队"));

    //计时器
    timeLabel = new QLabel(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

/*
    icon[0].addFile(QString::fromUtf8(":/image/1.png"));
    icon[1].addFile(QString::fromUtf8(":/image/2.png"));
    icon[2].addFile(QString::fromUtf8(":/image/3.png"));
    icon[3].addFile(QString::fromUtf8(":/image/4.png"));
    icon[4].addFile(QString::fromUtf8(":/image/5.png"));
    icon[5].addFile(QString::fromUtf8(":/image/6.png"));
    icon[6].addFile(QString::fromUtf8(":/image/7.png"));
    icon[7].addFile(QString::fromUtf8(":/image/8.png"));
    icon[8].addFile(QString::fromUtf8(":/image/9.png"));*/

    QString img[9];
    for(int i=0;i<9;i++){
        img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
        icon[i].addFile(img[i]);
    }

    icon[9].addFile(QString::fromUtf8(":/image/hong.jpg"));
    icon[10].addFile(QString::fromUtf8(":/image/lv.jpg"));
    icon[11].addFile(QString::fromUtf8(":/image/lan.jpg"));
    icon[12].addFile(QString::fromUtf8(":/image/lan.jpg"));
    icon[13].addFile(QString::fromUtf8(":/image/hong.jpg"));
    icon[14].addFile(QString::fromUtf8(":/image/lv.jpg"));
    icon[15].addFile(QString::fromUtf8(":/image/lv.jpg"));
    icon[16].addFile(QString::fromUtf8(":/image/lan.jpg"));
    icon[17].addFile(QString::fromUtf8(":/image/hong.jpg"));

    QStringList color;
    //我们给相邻的宫给上不同的颜色，便于区分
    color   <<"background-color:rgb(145, 184, 193)"//粉红
            <<"background-color:rgb(86, 130, 129)"//绿
            <<"background-color:rgb(199, 216, 217)"//淡钢蓝
            <<"background-color:rgb(199, 216, 217)"
            <<"background-color:rgb(145, 184, 193)"
            <<"background-color:rgb(86, 130, 129)"
            <<"background-color:rgb(86, 130, 129)"
            <<"background-color:rgb(199, 216, 217)"
            <<"background-color:rgb(145, 184, 193)";
    for(int r=0;r<9;r++)
    {

        for(int c=0;c<9;c++)
        {
            _btn[r][c].setFixedSize(40,40); //65,65
            QFont ft(nullptr,25);  //35
            _btn[r][c].setFont(ft);
            _btn[r][c].setText("");
            _btn[r][c].setEnabled(true);
            int tor=r/3,toc=c/3;
            int tar=tor*3+toc;
            _btn[r][c].setStyleSheet(color[tar]);//这里的默认字体是黑色，正好能让我们区分开
            ui->gridLayout->addWidget(&_btn[r][c],r,c);
            connect(&_btn[r][c],&QPushButton::clicked,[=](){
                QPoint point=this->cursor().pos();
                Form* fm = new Form(point,0,this,r,c,skin);
                fm->exec();
            });
        }
    }
    //选择难度
    QMessageBox* choice=new QMessageBox(this);
    choice->setWindowTitle(QStringLiteral("难度选择"));
    choice->setText(QStringLiteral("请选择数独题目难度："));
    choice->setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel | QMessageBox::Ok);
    choice->setButtonText(QMessageBox::Yes,QStringLiteral("简单模式"));
    choice->setButtonText(QMessageBox::Cancel,QStringLiteral("困难模式"));
    choice->setButtonText(QMessageBox::Ok,QStringLiteral("普通模式"));
    choice->setDefaultButton(QMessageBox::Yes);//默认难度为简单
    auto tmp=choice->exec();
    cnt=0;//cnt是初始给玩家的梳数字数
    if(tmp==QMessageBox::Yes)//选择简单难度
    {   timerSeconds=0;
        create(40);
        cnt=40;
        type=1;
         ui->diffShower->setTitle(QStringLiteral("简单模式"));
    }
    else if(tmp==QMessageBox::Ok)//选择中等难度
    {
        timerSeconds=0;
        create(32);
        cnt=32;
        type=2;
        ui->diffShower->setTitle(QStringLiteral("普通模式"));
    }
    else if(tmp==QMessageBox::Cancel)//选择困难难度
    {
        timerSeconds=0;
        create(24);
        cnt=24;
        type=3;
        ui->diffShower->setTitle(QStringLiteral("困难模式"));
    }


    connect(ui->actionsimple,&QAction::triggered,[=](){
        type=1;
        ui->diffShower->setTitle(QStringLiteral("简单模式"));
        timerSeconds=0;
        timeLabel->setText("Time: " + QString::number(timerSeconds) + " s");
        timer->start(1000);

        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                clearNum(i,j); //555555555555555555
            }
        }

        QRandomGenerator rnd;
        rnd.seed(time(0));
        int mid[9]={0};
        bool use[9]={0};
        for(int i=0;i<9;i++)
        {
            bool flag=1;
            while(flag)
            {
                int tmp=(rnd()%9+9)%9;
                if(!use[tmp])
                {
                    use[tmp]=1;
                    mid[i]=tmp;
                    flag=0;
                }
            }
        }
        int num[9][9]=
        {
            {mid[8],mid[6],mid[7],mid[2],mid[0],mid[1],mid[5],mid[3],mid[4]},
            {mid[2],mid[0],mid[1],mid[5],mid[3],mid[4],mid[8],mid[6],mid[7]},
            {mid[5],mid[3],mid[4],mid[8],mid[6],mid[7],mid[2],mid[0],mid[1]},
            {mid[6],mid[7],mid[8],mid[0],mid[1],mid[2],mid[3],mid[4],mid[5]},
            {mid[0],mid[1],mid[2],mid[3],mid[4],mid[5],mid[6],mid[7],mid[8]},
            {mid[3],mid[4],mid[5],mid[6],mid[7],mid[8],mid[0],mid[1],mid[2]},
            {mid[7],mid[8],mid[6],mid[1],mid[2],mid[0],mid[4],mid[5],mid[3]},
            {mid[1],mid[2],mid[0],mid[4],mid[5],mid[3],mid[7],mid[8],mid[6]},
            {mid[4],mid[5],mid[3],mid[7],mid[8],mid[6],mid[1],mid[2],mid[0]}
        };

        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                num[i][j]++;
                //set_Num(i,j,num[i][j]);//我们这里还有记好我们生成的数独，因为我们使用查看答案还是要用到的
            }
        }
        shuffle(num,10);//打乱
        for(int i=0;i<9;i++)for(int j=0;j<9;j++)set_Num(i,j,num[i][j]);//需要打乱后再set
        //调试代码
        //for(int i=0;i<9;i++)
                //cout<<num[i][0]<<" "<<num[i][1]<<" "<<num[i][2]<<" "<<num[i][3]<<" "<<num[i][4]<<" "<<num[i][5]<<" "<<num[i][6]<<" "<<num[i][7]<<" "<<num[i][8];
        bool s[81]={0};
        int count=0;
        while(count!=cnt)
        {
            int tmp=(rnd()%81+81)%81;
            if(s[tmp]==0) s[tmp]=1,count++;
        }

        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                int tar=i*9+j;
                if(s[tar]==1)
                {
                   // _btn[i][j].setText(QString::number(num[i][j]));
                    if(num[i][j]==1)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[0]);
                        _btn[i][j].setIconSize(QSize(41,41));}

                    if(num[i][j]==2)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[1]);
                        _btn[i][j].setIconSize(QSize(41,40));}

                    if(num[i][j]==3)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[2]);
                        _btn[i][j].setIconSize(QSize(40,41));}

                    if(num[i][j]==4)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[3]);
                        _btn[i][j].setIconSize(QSize(40,40));}

                    if(num[i][j]==5)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[4]);
                        _btn[i][j].setIconSize(QSize(40,40));}

                    if(num[i][j]==6)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[5]);
                        _btn[i][j].setIconSize(QSize(39,40));}

                    if(num[i][j]==7)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[6]);
                        _btn[i][j].setIconSize(QSize(40,39));}

                    if(num[i][j]==8)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[7]);
                        _btn[i][j].setIconSize(QSize(39,39));}

                    if(num[i][j]==9)
                    {   _btn[i][j].setFixedSize(39,39);
                        _btn[i][j].setIcon(icon[8]);
                        _btn[i][j].setIconSize(QSize(39,39));}
                    //_btn[i][j].setStyleSheet("background-color:rgb(0,255,0)");
                    _btn[i][j].setEnabled(false);
                }
                else
                {
                    _btn[i][j].setText("");
                    _btn[i][j].setEnabled(true);
                }

            }
        }


        //               clearAllNum();
//                timerSeconds=0;
//                create(40);
//                cnt=40;

    });
    connect(ui->actionmiddle,&QAction::triggered,[=](){
                clearAllNum();
                timerSeconds=0;
                create(32);
                cnt=32;
                type=2;
                ui->diffShower->setTitle(QStringLiteral("普通模式"));
    });
    connect(ui->actionhard,&QAction::triggered,[=](){
                clearAllNum();
                timerSeconds=0;
                create(24);
                cnt=24;
                type=3;
                ui->diffShower->setTitle(QStringLiteral("困难模式"));

    });
    //添加排行榜
    QAction* actionHighScore=new QAction(QStringLiteral("排行榜"));
    ui->sudokuBar->addAction(actionHighScore);
    connect(actionHighScore,&QAction::triggered,[=](){
            QMainWindow* hs=new highscore();
            hs->show();
        });
    /*connect(ui->actionHighScore,&QAction::triggered,[=](){
        QMainWindow* hs=new highscore();
        hs->show();
    });*/
    //hovered triggered mousePressEvent
/*
    connect(ui->menuHighScore,&mQMenu::menuclicked,[=](){
        QMainWindow* hs=new highscore();
        hs->show();
    });*/
    //添加皮肤
    QMenu* skinMenu=new QMenu(QStringLiteral("使用皮肤"));
    QAction* humanSkin=new QAction(QStringLiteral("human"));
    QAction* blueSkin=new QAction(QStringLiteral("blue"));
    QAction* colorfulSkin=new QAction(QStringLiteral("colorful"));
    QAction* dinosaurSkin=new QAction(QStringLiteral("dinosaur"));
    QAction* jointSkin=new QAction(QStringLiteral("joint"));
    QAction* lightSkin=new QAction(QStringLiteral("light"));
    QAction* pokerSkin=new QAction(QStringLiteral("poker"));
    QList<QAction*> skinList;
    skinList.append(humanSkin);
    skinList.append(blueSkin);
    skinList.append(colorfulSkin);
    skinList.append(dinosaurSkin);
    skinList.append(jointSkin);
    skinList.append(lightSkin);
    skinList.append(pokerSkin);
    skinMenu->addActions(skinList);
    ui->sudokuBar->addMenu(skinMenu);
    QAction* currentSkin=new QAction(QStringLiteral("blue"));
    ui->sudokuBar->addAction(currentSkin);
    //connect(skinMenu,&QMenu::triggered,[&](){
    //connect(skinMenu,&QAction::triggered,[=](){
    /*connect(humanSkin,&QAction::triggered,[=](){
        //QAction *skinSelected = (QAction*)this->sender();
        QAction *skinSelected = qobject_cast<QAction *>(sender());
        cout<<skinSelected;
        //cout<<this->sender();
    });*/

    connect(humanSkin,&QAction::triggered,[=](){const QString str="human";skin=str;currentSkin->setText(str);    QString img[9];
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }

    });
    /*connect(blueSkin,&QAction::triggered,[=](){const QString str="blue";skin=str;currentSkin->setText(str);
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }
    });*/
    connect(blueSkin,&QAction::triggered,[=](){const QString str="blue";skin=str;currentSkin->setText(str);    QString img[9];
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }

    });
    connect(colorfulSkin,&QAction::triggered,[=](){const QString str="colorful";skin=str;currentSkin->setText(str);    QString img[9];
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }

    });
    //connect(colorfulSkin,&QAction::triggered,[=](){const QString str="colorful";skin=str;currentSkin->setText(str);});
    connect(dinosaurSkin,&QAction::triggered,[=](){const QString str="dinosaur";skin=str;currentSkin->setText(str);    QString img[9];
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }

    });
    //connect(dinosaurSkin,&QAction::triggered,[=](){const QString str="dinosaur";skin=str;currentSkin->setText(str);});
    connect(jointSkin,&QAction::triggered,[=](){const QString str="joint";skin=str;currentSkin->setText(str);    QString img[9];
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }

    });
    //connect(jointSkin,&QAction::triggered,[=](){const QString str="joint";skin=str;currentSkin->setText(str);});
    connect(lightSkin,&QAction::triggered,[=](){const QString str="light";skin=str;currentSkin->setText(str);    QString img[9];
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }

    });
    //connect(lightSkin,&QAction::triggered,[=](){const QString str="light";skin=str;currentSkin->setText(str);});
    connect(pokerSkin,&QAction::triggered,[=](){const QString str="poker";skin=str;currentSkin->setText(str);    QString img[9];
        for(int i=0;i<9;i++){
            img[i]=QString(":/image/")+skin+QString("/")+QString::number(i+1)+QString(".png");
            icon[i].addFile(img[i]);
        }

    });
    //connect(pokerSkin,&QAction::triggered,[=](){const QString str="poker";skin=str;currentSkin->setText(str);});

    //点击游戏帮助后弹出一个消息对话框
    connect(ui->btn_help,&QPushButton::clicked,[=](){
        timer->stop();
        QMessageBox::information(this,"help",QStringLiteral("数独是源自18世纪瑞士的一种数学游戏。是一种"
                                             "运用纸、笔进行演算的逻辑游戏。玩家需要根据9×"
                                             "9盘面上的已知数字，推理出所有剩余空格的数字，"
                                             "并满足每一行、每一列、每一个粗线宫（3*3）内的数"
                                             "字均含1-9，不重复。\n数独盘面是个九宫，每一宫又"
                                             "分为九个小格。"
                                             "在这八十一格中给出一定的已知数字和解题条"
                                             "件，利用逻辑和推理，在其他的空格上填入1-"
                                             "9的数字。使1-9每个数字在每一行、每一列和"
                                             "每一宫中都只出现一次，所以又称“九宫格”。(以上全部摘自百度百科)\n"
                                             "鼠标点击每个小格子即可选择要填入的数字或者清除小格子的数字。\n点击提交答案即可检验你的答案是否正确"
                                             "。\n点击查看答案程序会自动为你填上最终答案。\n点击生成局面即能再来一局。\n"));
        timer->start(1000);
    });
    //点击查看答案后填上最终答案
    connect(ui->btn_answer,&QPushButton::clicked,[=](){
        timer->stop();
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                setNum(i,j,_num[i][j]);
            }
        }
    });
    //这里又copy了一遍上面create函数的代码，主要自己太懒了
    connect(ui->btn_create,&QPushButton::clicked,[=](){
        timerSeconds=0;
        timeLabel->setText("Time: " + QString::number(timerSeconds) + " s");
        timer->start(1000);
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                clearNum(i,j); //555555555555555555
            }
        }

        QRandomGenerator rnd;
        rnd.seed(time(0));
        int mid[9]={0};
        bool use[9]={0};
        for(int i=0;i<9;i++)
        {
            bool flag=1;
            while(flag)
            {
                int tmp=(rnd()%9+9)%9;
                if(!use[tmp])
                {
                    use[tmp]=1;
                    mid[i]=tmp;
                    flag=0;
                }
            }
        }
        int num[9][9]=
        {
            {mid[8],mid[6],mid[7],mid[2],mid[0],mid[1],mid[5],mid[3],mid[4]},
            {mid[2],mid[0],mid[1],mid[5],mid[3],mid[4],mid[8],mid[6],mid[7]},
            {mid[5],mid[3],mid[4],mid[8],mid[6],mid[7],mid[2],mid[0],mid[1]},
            {mid[6],mid[7],mid[8],mid[0],mid[1],mid[2],mid[3],mid[4],mid[5]},
            {mid[0],mid[1],mid[2],mid[3],mid[4],mid[5],mid[6],mid[7],mid[8]},
            {mid[3],mid[4],mid[5],mid[6],mid[7],mid[8],mid[0],mid[1],mid[2]},
            {mid[7],mid[8],mid[6],mid[1],mid[2],mid[0],mid[4],mid[5],mid[3]},
            {mid[1],mid[2],mid[0],mid[4],mid[5],mid[3],mid[7],mid[8],mid[6]},
            {mid[4],mid[5],mid[3],mid[7],mid[8],mid[6],mid[1],mid[2],mid[0]}
        };

        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                num[i][j]++;
                //set_Num(i,j,num[i][j]);//我们这里还有记好我们生成的数独，因为我们使用查看答案还是要用到的
            }
        }
        shuffle(num,10);//打乱
        for(int i=0;i<9;i++)for(int j=0;j<9;j++)set_Num(i,j,num[i][j]);//需要打乱后再set
        //调试代码
        //for(int i=0;i<9;i++)
                //cout<<num[i][0]<<" "<<num[i][1]<<" "<<num[i][2]<<" "<<num[i][3]<<" "<<num[i][4]<<" "<<num[i][5]<<" "<<num[i][6]<<" "<<num[i][7]<<" "<<num[i][8];
        bool s[81]={0};
        int count=0;
        while(count!=cnt)
        {
            int tmp=(rnd()%81+81)%81;
            if(s[tmp]==0) s[tmp]=1,count++;
        }

        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                int tar=i*9+j;
                if(s[tar]==1)
                {
                   // _btn[i][j].setText(QString::number(num[i][j]));
                    if(num[i][j]==1)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[0]);
                        _btn[i][j].setIconSize(QSize(41,41));}

                    if(num[i][j]==2)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[1]);
                        _btn[i][j].setIconSize(QSize(41,40));}

                    if(num[i][j]==3)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[2]);
                        _btn[i][j].setIconSize(QSize(40,41));}

                    if(num[i][j]==4)
                    {   _btn[i][j].setFixedSize(41,41);
                        _btn[i][j].setIcon(icon[3]);
                        _btn[i][j].setIconSize(QSize(40,40));}

                    if(num[i][j]==5)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[4]);
                        _btn[i][j].setIconSize(QSize(40,40));}

                    if(num[i][j]==6)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[5]);
                        _btn[i][j].setIconSize(QSize(39,40));}

                    if(num[i][j]==7)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[6]);
                        _btn[i][j].setIconSize(QSize(40,39));}

                    if(num[i][j]==8)
                    {   _btn[i][j].setFixedSize(40,40);
                        _btn[i][j].setIcon(icon[7]);
                        _btn[i][j].setIconSize(QSize(39,39));}

                    if(num[i][j]==9)
                    {   _btn[i][j].setFixedSize(39,39);
                        _btn[i][j].setIcon(icon[8]);
                        _btn[i][j].setIconSize(QSize(39,39));}
                    //_btn[i][j].setStyleSheet("background-color:rgb(0,255,0)");
                    _btn[i][j].setEnabled(false);
                }
                else
                {
                    _btn[i][j].setText("");
                    _btn[i][j].setEnabled(true);
                }

            }
        }
    });

    connect(ui->btn_submit,&QPushButton::clicked,[=](){
        int col[9]={0},row[9]={0},cell[3][3]={{0},{0},{0}};
        bool flag=1;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                //int num=_btn[i][j].text().toInt()-1;
                int num = 0;

                if((_btn[i][j].size().width()==41)&&(_btn[i][j].size().height()==41)&&
                        (_btn[i][j].iconSize().width()==41)&&(_btn[i][j].iconSize().height()==41))
                {num = 0;}

                if((_btn[i][j].size().width()==41)&&(_btn[i][j].size().height()==41)&&
                        (_btn[i][j].iconSize().width()==41)&&(_btn[i][j].iconSize().height()==40))
                {num = 1;}

                if((_btn[i][j].size().width()==41)&&(_btn[i][j].size().height()==41)&&
                        (_btn[i][j].iconSize().width()==40)&&(_btn[i][j].iconSize().height()==41))
                {num = 2;}

                if((_btn[i][j].size().width()==41)&&(_btn[i][j].size().height()==41)&&
                        (_btn[i][j].iconSize().width()==40)&&(_btn[i][j].iconSize().height()==40))
                {num = 3;}

                if((_btn[i][j].size().width()==40)&&(_btn[i][j].size().height()==40)&&
                        (_btn[i][j].iconSize().width()==40)&&(_btn[i][j].iconSize().height()==40))
                {num = 4;}

                if((_btn[i][j].size().width()==40)&&(_btn[i][j].size().height()==40)&&
                        (_btn[i][j].iconSize().width()==39)&&(_btn[i][j].iconSize().height()==40))
                {num = 5;}

                if((_btn[i][j].size().width()==40)&&(_btn[i][j].size().height()==40)&&
                        (_btn[i][j].iconSize().width()==40)&&(_btn[i][j].iconSize().height()==39))
                {num = 6;}

                if((_btn[i][j].size().width()==40)&&(_btn[i][j].size().height()==40)&&
                        (_btn[i][j].iconSize().width()==39)&&(_btn[i][j].iconSize().height()==39))
                {num = 7;}

                if((_btn[i][j].size().width()==39)&&(_btn[i][j].size().height()==39)&&
                        (_btn[i][j].iconSize().width()==39)&&(_btn[i][j].iconSize().height()==39))
                {num = 8;}

                // qDebug() <<QStringLiteral("当前值为：") << num;
                if(row[i]>>num&1||col[j]>>num&1||cell[i/3][j/3]>>num&1)
                {
                    flag=0;
                }
                col[j]|=1<<num;
                row[i]|=1<<num;
                cell[i/3][j/3]|=1<<num;
            }
        }
        if(flag==1)

        {
           // QMessageBox acceptBox(QMessageBox::information(this,"congratulations","Accepted"));
           /* QMessageBox MyBox(QMessageBox::Question,("Bingo"),QStringLiteral("\n\n恭\n喜\n你\n!"));
            QPixmap map(":/image/sun.png");

            MyBox.setIconPixmap(QPixmap(":/image/sun.png"));
            MyBox.exec();
            */

            //弹出恭喜，输入姓名，写入数据库
            QMainWindow* si=new scoreinput(nullptr,type,timerSeconds);
            si->show();



        }
        else

        {   //Icon _iconA;
            //_iconA.addFile(QString::fromUtf8(":/image/1.png"), QSize(50,50), QIcon::Normal, QIcon::Off);
            //QMessageBox::information(this,"what a pity","Wrong Answer");
            QMessageBox MyBox(QMessageBox::Question,"Bingo",QStringLiteral("\n继\n续\n努\n力\n!"));
            MyBox.setIconPixmap(QPixmap(":/image/duck.png"));
            MyBox.exec();
        }
    });
    timeLabel->setGeometry(280,610,100, 60);
    timeLabel->setText("Time: " + QString::number(timerSeconds) + " s");
    timer->start(1000);
}
void Widget::setNum(int r, int c, int num)
{
    QFont font(nullptr,5);
    _btn[r][c].setFont(font);
    _btn[r][c].setText(QString::number(num));
    if(_btn[r][c].text()=="1")
   {
       _btn[r][c].setFixedSize(41,41);
       _btn[r][c].setIcon(icon[0]);
       _btn[r][c].setIconSize(QSize(41,41));}

   if(_btn[r][c].text()=="2")
   {   _btn[r][c].setFixedSize(41,41);
       _btn[r][c].setIcon(icon[1]);
       _btn[r][c].setIconSize(QSize(41,40));}

   if(_btn[r][c].text()=="3")
   {   _btn[r][c].setFixedSize(41,41);
       _btn[r][c].setIcon(icon[2]);
       _btn[r][c].setIconSize(QSize(40,41));}

   if(_btn[r][c].text()=="4")
   {   _btn[r][c].setFixedSize(41,41);
       _btn[r][c].setIcon(icon[3]);
       _btn[r][c].setIconSize(QSize(40,40));}

   if(_btn[r][c].text()=="5")
   {   _btn[r][c].setFixedSize(40,40);
       _btn[r][c].setIcon(icon[4]);
       _btn[r][c].setIconSize(QSize(40,40));}

   if(_btn[r][c].text()=="6")
   {   _btn[r][c].setFixedSize(40,40);
       _btn[r][c].setIcon(icon[5]);
       _btn[r][c].setIconSize(QSize(39,40));}

   if(_btn[r][c].text()=="7")
   {   _btn[r][c].setFixedSize(40,40);
       _btn[r][c].setIcon(icon[6]);
       _btn[r][c].setIconSize(QSize(40,39));}

   if(_btn[r][c].text()=="8")
   {   _btn[r][c].setFixedSize(40,40);
       _btn[r][c].setIcon(icon[7]);
       _btn[r][c].setIconSize(QSize(39,39));}

   if(_btn[r][c].text()=="9")
   {   _btn[r][c].setFixedSize(39,39);
       _btn[r][c].setIcon(icon[8]);
       _btn[r][c].setIconSize(QSize(39,39));}
      _btn[r][c].setText("");
}

void Widget::clearNum(int r, int c)
{

    _btn[r][c].setText("");   //红绿蓝蓝红绿绿蓝红

    int tor=r/3,toc=c/3;
    int tar=tor*3+toc;
    _btn[r][c].setIcon(icon[tar+9]);
    _btn[r][c].setIconSize(QSize(40,40));


//        if(((r>=0&&r<3)&&(c>=0&&c<3))||((r>=3&&r<6)&&(c>=3&&c<6))||((r>=6&&r<9)&&(c>=6&&c<9)))
//        {
//           _btn[r][c].setIcon(icon[9]);
//           _btn[r][c].setIconSize(QSize(40,40));
//        }
//        else if(((r>=3&&r<6)&&(c>=0&&c<3))||((r>=6&&r<9)&&(c>=3&&c<6))||((r>=0&&r<3)&&(c>=6&&c<9)))
//        {
//           _btn[r][c].setIcon(icon[10]);
//           _btn[r][c].setIconSize(QSize(40,40));
//        }
//        else if(((r>=6&&r<9)&&(c>=0&&c<3))||((r>=0&&r<3)&&(c>=3&&c<6))||((r>=3&&r<6)&&(c>=6&&c<9)))
//        {
//           _btn[r][c].setIcon(icon[11]);
//           _btn[r][c].setIconSize(QSize(40,40));
//        }
}

void Widget::clearAllNum()
{
    for(int m=0;m<9;m++)
    {
        for(int n=0;n<9;n++)
        {
            clearNum(m,n);

        }
    }
}

//这个可能等会就不用了
bool Widget::check()
{
    int col[9]={0},row[9]={0},cell[3][3]={0};
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            int num=_btn[i][j].text().toInt()-1;
            if(col[i]>>num&1||col[j]>>num&1||cell[i/3][j/3]>>num&1)
            {
                return false;
            }
            col[j]|=1<<num;
            row[i]|=1<<num;
            cell[i/3][j/3]|=1<<num;
        }
    }
    return true;
}

void Widget::updateTimer()
{
    // 计时器计时
    timerSeconds++;
    timeLabel->setText("Time: " + QString::number(timerSeconds) + " s");
    qDebug() << timerSeconds;
}

Widget::~Widget()
{
    delete ui;
}

template<int n, int m>
void Widget::shuffle(int (&mat)[n][m], int nShuffle)
{
    int unShf[9][9];
    memcpy(unShf,mat,sizeof(unShf));
    QRandomGenerator rndShuffle;
    //rndShuffle.seed(time(0));
    rndShuffle.seed(QTime(0,0,0).secsTo(QTime::currentTime()));
    while(nShuffle--){
        bool rFlag[9]={0};
        bool cFlag[9]={0};
        int rShf[9]={0};
        int cShf[9]={0};
        int tmp=0;
        for(int i=0;i<9;){
            tmp=rndShuffle()%3+(i/3)*3;
            if(!rFlag[tmp]){
                rFlag[tmp]=1;
                rShf[i]=tmp;
                i++;
            }
        }
        for(int i=0;i<9;){
            tmp=rndShuffle()%3+(i/3)*3;
            if(!cFlag[tmp]){
                cFlag[tmp]=1;
                cShf[i]=tmp;
                i++;
            }
        }

        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                mat[i][j]=unShf[rShf[i]][j];
            }
        }
        memcpy(unShf,mat,sizeof(unShf));
       for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                mat[i][j]=unShf[i][cShf[j]];
            }
        }
   //cout<<rShf[0]<<" "<<rShf[1]<<" "<<rShf[2]<<" "<<rShf[3]<<" "<<rShf[4]<<" "<<rShf[5]<<" "<<rShf[6]<<" "<<rShf[7]<<" "<<rShf[8];
   //cout<<cShf[0]<<" "<<cShf[1]<<" "<<cShf[2]<<" "<<cShf[3]<<" "<<cShf[4]<<" "<<cShf[5]<<" "<<cShf[6]<<" "<<cShf[7]<<" "<<cShf[8];
   //cout<<endl;
   }
}
