#include "scoreinput.h"
#include "ui_scoreinput.h"
#include "SqliteOperator.h"
#include<QDebug>
scoreinput::scoreinput(QWidget *parent,int t,int g) :
    QMainWindow(parent),
    ui(new Ui::scoreinput),type(t),grade(g)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("Bingo！"));
    initUI();
}

scoreinput::~scoreinput()
{
    delete ui;
}

void scoreinput::initUI()
{
    QString str;
    if(this->type==1){
        str=QStringLiteral("简单模式");
    }else if(this->type==2){
        str=QStringLiteral("普通模式");
    }else{
        str=QStringLiteral("困难模式");
    }
    ui->typeShower->setText(str+QStringLiteral("数独已完成！"));
    ui->secShower->setText(QStringLiteral("耗时 ")+QString::number(grade)+QStringLiteral(" 秒完成"));
    ui->picLabel->setPixmap(QPixmap(":/image/sun.png"));

    connect(ui->submmitBtn,&QPushButton::clicked,[=](){
        SqliteOperator sqlTest;
        sqlTest.openDb();
        //如果没有，则创建数据表
        QString str1 = QString("sudoku");
        if(!sqlTest.isTableExist(str1)){sqlTest.createTable();}
        qDebug() << "isTabelExist：" <<sqlTest.isTableExist(str1);
        int num=sqlTest.getDbNum();
        //w2dba w2dbaTest1 = {1, "zhangSan",QStringLiteral("困难模式"), 24};
        w2dba w2dbaTest1 = {num,
                            ui->nameInput->text(),
                            str,
                            grade};
        sqlTest.singleInsertData(w2dbaTest1);
        // 查询全部数据
        sqlTest.queryTable();
        qDebug() << endl;
        sqlTest.closeDb();
    });
}
