#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    vlay = new QVBoxLayout();
    dialog00 = new QDialog(this);
    dialog01 = new QDialog(this);
    dialog10 = new QDialog(this);
    dialog11 = new QDialog(this);
    view00 = new QTableView();
    view01 = new QTableView();
    view10 = new QTableView();
    view11 = new QTableView();
    twgt = new QTableWidget();
    db = new DB();


    QLabel *lbl = new QLabel("\tАналитический регистр налогового учета доходов, полученных\n"
                              "за расчетно-кассовое обслуживание карточных счетов за май 2018 г.\n"
                              "\nСим. 2710404, 2720405\n");
    vlay->addWidget(lbl, 0, Qt::AlignCenter);


    accounts0.push_back(std::make_pair<QString, QString>("70601810500002710404", "40817810900000003333"));
    accounts0.push_back(std::make_pair<QString, QString>("70601810500012710404", "40817810900000013333"));
    /*--------------------------------------------------------------------------------------------------*/
    accounts1.push_back(std::make_pair<QString, QString>("70601810900002720405", "40817810900000023333"));
    accounts1.push_back(std::make_pair<QString, QString>("70601810900102720405", "40817810900000033333"));

    make_table(dialog00, accounts0[0].first, turnover00);
    make_table(dialog01, accounts0[1].first, turnover01);

    make_table(dialog10, accounts1[0].first, turnover10);
    make_table(dialog11, accounts1[1].first, turnover11);

    twgt->verticalHeader()->hide();
    twgt->horizontalHeader()->setStretchLastSection(true);
    twgt->setColumnCount(4);
    twgt->setRowCount(3);
    QStringList list;
    list.push_back("Наименование\nпоказателя");
    list.push_back("Источник\nинформации");
    list.push_back("Май");
    list.push_back("С начала года");
    twgt->setHorizontalHeaderLabels(list);

    twgt->resizeColumnToContents(1);

    twgt->setItem(0, 0, new QTableWidgetItem("Вознаграждение за\nоткрытие и ведение\nкарточных счетов"));
    twgt->setItem(0, 1, new QTableWidgetItem("Сим.\n2710404"));
    twgt->resizeRowToContents(0);

    twgt->setItem(1, 0, new QTableWidgetItem("Вознаграждение за\nрасчетное и кассовое\nобслуживание\nкарточных счетов"));
    twgt->setItem(1, 1, new QTableWidgetItem("Сим.\n2720405"));
    twgt->resizeRowToContents(1);
    twgt->resizeColumnToContents(0);

    twgt->setItem(2, 0, new QTableWidgetItem("Итого по\nрегистру"));
    twgt->resizeRowToContents(2);

    twgt->verticalHeader()->setStretchLastSection(true);

    int total0 = 0, total1 = 0;
    total0 = turnover00 + turnover01;
    total1 = turnover10 + turnover11;
    twgt->setItem(0, 2, new QTableWidgetItem(std::to_string(total0).c_str()));
    twgt->setItem(1, 2, new QTableWidgetItem(std::to_string(total1).c_str()));
    twgt->setItem(2, 2, new QTableWidgetItem(std::to_string(total0 + total1).c_str()));


    vlay->addWidget(twgt);

    ui->centralWidget->setLayout(vlay);

//        db->fillDB(accounts0[0].first, accounts0[0].second, "01.05.2018", 200, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts0[0].first, accounts0[0].second, "01.05.2018", 200, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts0[0].second, accounts0[0].first, "02.05.2018", 100, db->OPERATION_TYPE::CREDIT);
//        db->fillDB(accounts0[0].second, accounts0[0].first, "02.05.2018", 100, db->OPERATION_TYPE::CREDIT);
//        db->fillDB(accounts0[1].first, accounts0[1].second, "03.05.2018", 500, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts0[1].first, accounts0[1].second, "03.05.2018", 500, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts0[1].second, accounts0[1].first, "05.05.2018", 250, db->OPERATION_TYPE::CREDIT);
//        db->fillDB(accounts0[1].second, accounts0[1].first, "05.05.2018", 250, db->OPERATION_TYPE::CREDIT);

//        db->fillDB(accounts1[0].first, accounts1[0].second, "05.05.2018", 300, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts1[0].first, accounts1[0].second, "05.05.2018", 300, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts1[0].second, accounts1[0].first, "10.05.2018", 50, db->OPERATION_TYPE::CREDIT);
//        db->fillDB(accounts1[0].second, accounts1[0].first, "10.05.2018", 50, db->OPERATION_TYPE::CREDIT);
//        db->fillDB(accounts1[1].first, accounts1[1].second, "13.05.2018", 150, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts1[1].first, accounts1[1].second, "13.05.2018", 150, db->OPERATION_TYPE::DEBIT);
//        db->fillDB(accounts1[1].second, accounts1[1].first, "15.05.2018", 50, db->OPERATION_TYPE::CREDIT);
//        db->fillDB(accounts1[1].second, accounts1[1].first, "18.05.2018", 50, db->OPERATION_TYPE::CREDIT);


    connect(twgt, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(item_clicked()));
}

void MainWindow::item_clicked(){

    dialogLay = new QVBoxLayout();

    if(twgt->currentIndex().row() == 0){ //отображаю первую таблицу
        dialog00->show();
        dialog01->show();
    } else if(twgt->currentIndex().row() == 1){ //отображаю вторую таблицу
        dialog10->show();
        dialog11->show();
    }
}

void MainWindow::make_table(QDialog *dialog, QString account, int &turnover){
    QSqlQueryModel *model = new QSqlQueryModel();
    QTableView *view = new QTableView();
    model->setQuery(QString("SELECT * FROM credit WHERE debitNum = '%1' OR  creditNum = '%2'").arg(account).arg(account));
    model->setHeaderData(1, Qt::Horizontal, "Счет дебет");
    model->setHeaderData(2, Qt::Horizontal, "Счет кредит");
    model->setHeaderData(3, Qt::Horizontal, "Дата");
    model->setHeaderData(4, Qt::Horizontal, "Сумма дебета");
    model->setHeaderData(5, Qt::Horizontal, "Сумма кредита");

    int credit = 0, debit = 0;
    for(int i = 0; i < model->rowCount(); ++i){
        debit += model->data(model->index(i, 4)).toInt();
        credit += model->data(model->index(i, 5)).toInt();
    }
    turnover = debit - credit;

    view->setModel(model);
    view->hideColumn(0);
    view->resizeColumnsToContents();
    view->horizontalHeader()->setStretchLastSection(true);
    view->verticalHeader()->setStretchLastSection(true);
    view->resize(600, 150);
    dialogLay = new QVBoxLayout();
    dialogLay->addWidget(view);
    QLabel *lbl = new QLabel(QString("%1 \t\t %2\t\t").arg(std::to_string(debit).c_str()).arg(std::to_string(credit).c_str()));
    dialogLay->addWidget(lbl, 20, Qt::AlignRight);
    dialog->setLayout(dialogLay);
    dialog->resize(600, 200);
}

MainWindow::~MainWindow()
{
    delete ui;
}
