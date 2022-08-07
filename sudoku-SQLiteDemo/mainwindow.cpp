#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SqliteOperator.h"
#include<QRandomGenerator>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("数独连接SQLite数据库测试"));

    this->initUI();
    this->initSignalAndSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    ui->gameSelector->addItem(QStringLiteral("简单模式"));
    ui->gameSelector->addItem(QStringLiteral("普通模式"));
    ui->gameSelector->addItem(QStringLiteral("困难模式"));
    ui->nameInput->setText(QStringLiteral("玩家1"));
    ui->gradeInput->setText("102");
    //随机生成成绩记录
    QObject::connect(ui->genGradeBtn,&QPushButton::clicked,ui->nameInput,[=](){
        QRandomGenerator rnd;
        rnd.seed(time(0));
        ui->gameSelector->setCurrentIndex(rnd()%3);
        ui->nameInput->setText(QStringLiteral("玩家")+QString::number(rnd()%10));
        ui->gradeInput->setText(QString::number(rnd()%100));
    });

    //提交成绩
   /* QObject::connect(ui->submmitBtn,&QPushButton::clicked,ui->nameInput,[&sqlTest](){
        w2dba w2dbaTest1 = {1, "zhangSan",QStringLiteral("困难模式"), 24};
        sqlTest.singleInsertData(w2dbaTest1);
        // 查询全部数据
        sqlTest.queryTable();
        qDebug() << endl;
    });*/
    //提交成绩
    QObject::connect(ui->submmitBtn,&QPushButton::clicked,ui->nameInput,[=](){
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
                            ui->gameSelector->currentText(),
                            ui->gradeInput->text().toInt()};
        sqlTest.singleInsertData(w2dbaTest1);
        // 查询全部数据
        sqlTest.queryTable();
        qDebug() << endl;
        sqlTest.closeDb();
    });
    //显示排行榜
    QObject::connect(ui->getGradesBtn,&QPushButton::clicked,ui->highScore,[=](){
        SqliteOperator sqlTest;
        sqlTest.openDb();
        //如果没有，则创建数据表
        QString str1 = QString("sudoku");
        if(!sqlTest.isTableExist(str1)){sqlTest.createTable();}
        qDebug() << "isTabelExist：" <<sqlTest.isTableExist(str1);
        QString modeStr=ui->gameSelector->currentText();
        QString getDb=sqlTest.getGrades(modeStr);
        ui->highScore->setText(getDb);
        sqlTest.closeDb();
    });
}

void MainWindow::initSignalAndSlots()
{

}
