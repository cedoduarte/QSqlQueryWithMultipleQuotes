#include <QCoreApplication>
#include <QByteArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

static void openDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    qDebug() << "db.open:" << db.open();
}

static void createTable()
{
    QString sql = "create table if not exists mytable(id integer primary key autoincrement, content text)";
    QSqlQuery query;
    query.prepare(sql);
    qDebug() << "create mytable:" << query.exec();
}

static void insertData(const QByteArray &data)
{
    QString value = QString::fromLatin1(data);
    value = value.replace("\"", "\"\"");
    QString sql = QString("insert into mytable(content) values(\"%1\")").arg(value);
    QSqlQuery query;
    query.prepare(sql);
    qDebug() << "insert data:" << query.exec();
}

static QByteArray readTextFile()
{
    QFile F(":/input.txt");
    qDebug() << "input.txt opened:" << F.open(QIODevice::Text | QIODevice::ReadOnly);
    QByteArray data = F.readAll();
    F.close();
    return data;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    openDB();
    createTable();
    insertData(readTextFile());
    qDebug() << "done!";


    return a.exec();
}
