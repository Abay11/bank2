#include <db.h>


DB::DB(){
    bool isFileExists = QFile::exists(name);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);

    if(!db.open())
        qDebug() << "Error opening DB";

    query = new QSqlQuery(db);

    if(!isFileExists){
            qDebug() << query->exec("CREATE TABLE credit ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                   "debitNum TEXT NOT NULL,"
                                   "creditNum TEXT NOT NULL,"
                                   "date TEXT NOT NULL,"
                                   "d_sum INTEGER,"
                                   "c_sum INTEGER);"
                                   ) << " <- creating table";
        }
}

void DB::fillDB(QString debitNum, QString creditNum, QString date, int sum, DB::OPERATION_TYPE TYPE){
    if(TYPE){ //the operation type is debit
       query->prepare("INSERT INTO credit(debitNum, creditNum, date, d_sum)"
                     "VALUES (:debitNum, :creditNum, :date, :d_sum)");
       query->bindValue(":debitNum", debitNum);
       query->bindValue(":creditNum", creditNum);
       query->bindValue(":date", date);
       query->bindValue(":d_sum", sum);
       qDebug() << query->exec()  << " <- inserting into table";
    }else{ // the operation id credit
        query->prepare("INSERT INTO credit (debitNum, creditNum, date, c_sum)"
                      "VALUES (:debitNum, :creditNum, :date, :c_sum)");
        query->bindValue(":debitNum", debitNum);
        query->bindValue(":creditNum", creditNum);
        query->bindValue(":date", date);
        query->bindValue(":c_sum", sum);
        qDebug() << query->exec()  << " <- inserting into table";
    }
}

DB::~DB(){
    db.close();
    db.removeDatabase("SQLITE");
    qDebug() << "DB closed";
}
