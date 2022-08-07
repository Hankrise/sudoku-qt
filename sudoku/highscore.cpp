#include "highscore.h"
#include "ui_highscore.h"
#include "SqliteOperator.h"
#include<QRandomGenerator>
#include<QDebug>
highscore::highscore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::highscore)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("数独成绩排行榜"));
    initUI();
}

highscore::~highscore()
{
    delete ui;
}

void highscore::initUI()
{
    ui->gameSelector->addItem(QStringLiteral("简单模式"));
    ui->gameSelector->addItem(QStringLiteral("普通模式"));
    ui->gameSelector->addItem(QStringLiteral("困难模式"));
    SqliteOperator sqlTest;
    sqlTest.openDb();
    //如果没有，则创建数据表
    QString str1 = QString("sudoku");
    if(!sqlTest.isTableExist(str1)){sqlTest.createTable();}
    qDebug() << "isTabelExist：" <<sqlTest.isTableExist(str1);
    QString modeStr=ui->gameSelector->currentText();
    QString getDb=sqlTest.getGrades(modeStr);
    ui->scoreShower->setText(getDb);
    sqlTest.closeDb();
    //ui->gameSelector->setCurrentIndex(1);
    QObject::connect(ui->gameSelector,&QComboBox::currentTextChanged,ui->scoreShower,[=](){
        SqliteOperator sqlTest;
        sqlTest.openDb();
        //如果没有，则创建数据表
        QString str1 = QString("sudoku");
        if(!sqlTest.isTableExist(str1)){sqlTest.createTable();}
        qDebug() << "isTabelExist：" <<sqlTest.isTableExist(str1);
        QString modeStr=ui->gameSelector->currentText();
        QString getDb=sqlTest.getGrades(modeStr);
        ui->scoreShower->setText(getDb);
        sqlTest.closeDb();
    });
}
