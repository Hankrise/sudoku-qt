#include "sqliteoperator.h"

// 构造函数中初始化数据库对象，并建立数据库
SqliteOperator::SqliteOperator()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("MyDataBase.db");
    }
}

// 打开数据库
bool SqliteOperator::openDb()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
    }

    return true;
}

// 创建数据表
void SqliteOperator::createTable()
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery;
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE sudoku (\
                          id INT PRIMARY KEY NOT NULL,\
                          name TEXT NOT NULL,\
                          mode TEXT NOT NULL,\
                          grade INT NOT NULL)");
    sqlQuery.prepare(createSql);
    // 执行sql语句
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

// 判断数据库中某个数据表是否存在
bool SqliteOperator::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}

// 查询全部数据
void SqliteOperator::queryTable()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM sudoku");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            QString mode = sqlQuery.value(2).toString();
            int grade = sqlQuery.value(3).toInt();
            qDebug()<<QString("id:%1    name:%2    mode:%3    grade:%4").arg(id).arg(name).arg(mode).arg(grade);
        }
    }
}

// 插入单条数据
void SqliteOperator::singleInsertData(w2dba &singledb)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO sudoku VALUES(:id,:name,:mode,:grade)");
    sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":name", singledb.name);
    sqlQuery.bindValue(":mode", singledb.mode);
    sqlQuery.bindValue(":grade", singledb.grade);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

// 插入多条数据
void SqliteOperator::moreInsertData(QList<w2dba>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO sudoku VALUES(?,?,?,?)");
    QVariantList idList,nameList,modeList,gradeList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        nameList << moredb.at(i).name;
        modeList << moredb.at(i).mode;
        gradeList << moredb.at(i).grade;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(modeList);
    sqlQuery.addBindValue(gradeList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}

void SqliteOperator::modifyData(int id, QString name, QString mode, int grade)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE sudoku SET name=?,mode=?,grade=? WHERE id=?");
    sqlQuery.addBindValue(name);
    sqlQuery.addBindValue(mode);
    sqlQuery.addBindValue(grade);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

// 删除数据
void SqliteOperator::deleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM student WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

//删除数据表
void SqliteOperator::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}

void SqliteOperator::closeDb(void)
{
    database.close();
}

int SqliteOperator::getDbNum(void)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT Count(*) FROM sudoku");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int num = sqlQuery.value(0).toInt();
            qDebug()<<QString("num:%1").arg(num);
            return num;
        }
    }

}

QString SqliteOperator::getGrades(QString &mode)
{
    QSqlQuery sqlQuery;
    QString sqlLine="SELECT * FROM sudoku WHERE mode='"+mode+"' ORDER BY grade";
    //const std::string sqlLineStr=sqlLine.toStdString();

    sqlQuery.exec(sqlLine);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        QString rtn=QStringLiteral("---")+mode+QStringLiteral(" 成绩排行榜---\n");
        rtn=rtn+QStringLiteral("名次     姓名     成绩\n");
        int i=1;
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            QString mode = sqlQuery.value(2).toString();
            int grade = sqlQuery.value(3).toInt();
            qDebug()<<QString("id:%1    name:%2    mode:%3    grade:%4").arg(id).arg(name).arg(mode).arg(grade);
            rtn=rtn+QStringLiteral("第")+QString::number(i)+QStringLiteral("名    ");
            rtn=rtn+name+QStringLiteral("    ")+QString::number(grade)+QStringLiteral("秒\n");
            i++;
        }
        return rtn;
    }
return QStringLiteral("暂无成绩！");
}
