#ifndef DB_H
#define DB_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QFile>

class DB{
public:
    DB();
    ~DB();
    QString name = "bank.sqlite";
    QSqlDatabase db;
    QSqlQueryModel *model;
    QSqlQuery *query;
    enum OPERATION_TYPE{CREDIT, DEBIT};
    void fillDB(QString, QString, QString, int, OPERATION_TYPE);
};

#endif // DB_H
