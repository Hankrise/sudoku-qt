#include "mainwindow.h"

#include <QApplication>

#include <QCoreApplication>
#include "SqliteOperator.h"
#include <QString>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //数据库测试
if(0){
    //创建并打开SQLite数据库
    SqliteOperator sqlTest;
    sqlTest.openDb();

    // 创建数据表
    //sqlTest.createTable();

    // 判断数据表是否存在
    QString str1 = QString("sudoku");
    if(!sqlTest.isTableExist(str1)){sqlTest.createTable();}
    qDebug() << "isTabelExist：" <<sqlTest.isTableExist(str1);

    // 插入单条数据
    w2dba w2dbaTest1 = {1, "zhangSan",QStringLiteral("困难模式"), 24};
    w2dba w2dbaTest2 = {2, "lisi",QStringLiteral("简单模式"), 28};
    sqlTest.singleInsertData(w2dbaTest1);
    sqlTest.singleInsertData(w2dbaTest2);

    // 插入多条数据
    QList<w2dba> list;
    w2dba w2dbaTest3 = {3, "liwu",QStringLiteral("普通模式"), 26};
    w2dba w2dbaTest4 = {4, "niuer",QStringLiteral("困难模式"), 27};
    list.append(w2dbaTest3);
    list.append(w2dbaTest4);
    sqlTest.moreInsertData(list);
    // 查询全部数据
    sqlTest.queryTable();
    qDebug() << endl;

    // 修改数据
    sqlTest.modifyData(2, "modify",QStringLiteral("修改"), 10);
    // 查询全部数据
    sqlTest.queryTable();
    qDebug() << endl;

    // 删除数据
    sqlTest.deleteData(2);
    // 查询全部数据
    sqlTest.queryTable();
    qDebug() << endl;

    // 删除数据表
    QString str2 = QString("sudoku");
    sqlTest.deleteTable(str2);

    //关闭数据库
    sqlTest.closeDb();
}


    MainWindow w;
    w.show();
    return a.exec();
}
