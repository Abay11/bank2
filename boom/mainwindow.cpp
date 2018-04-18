#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    vlay = new QVBoxLayout();
    dialog = new QDialog(this);
    view0 = new QTableView();
    view1 = new QTableView();
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

    model0 = new QSqlQueryModel();

//            .arg(accounts0[0].first).arg(accounts0[1].first);
    model0->setQuery(QString("SELECT * FROM credit WHERE debitNum = '%1' OR creditNum = '%1' "
                             "OR debitNum = '%2' OR creditNum = '%2'").arg(accounts0[0].first).arg(accounts0[1].first));
    model0->setHeaderData(1, Qt::Horizontal, "Счет дебет");
    model0->setHeaderData(2, Qt::Horizontal, "Счет кредит");
    model0->setHeaderData(3, Qt::Horizontal, "Дата");
    model0->setHeaderData(4, Qt::Horizontal, "Сумма дебета");
    model0->setHeaderData(5, Qt::Horizontal, "Сумма кредита");

    view0->setModel(model0);
    view0->hideColumn(0);
    view0->resizeColumnsToContents();
    view0->horizontalHeader()->setStretchLastSection(true);
    view0->verticalHeader()->setStretchLastSection(true);
    view0->resize(600, 600);

    for(int i = 0; i < model0->columnCount(); ++i){
        debit0 += model0->data(model0->index(i, 3)).toInt();
        credit0 += model0->data(model0->index(i, 4)).toInt();
    }

    turnover0 = debit0 - credit0;

    model1 = new QSqlQueryModel();
    model1->setQuery(QString("SELECT * FROM credit"));

//    model1->setQuery(QString("SELECT * FROM credit WHERE debitNum = '%1' OR creditNum = '%1' "
//                             "OR debitNum = '%2' OR creditNum = '%2'").arg(accounts1[0].first).arg(accounts1[1].first));
    model1->setHeaderData(1, Qt::Horizontal, "Счет дебет");
    model1->setHeaderData(2, Qt::Horizontal, "Счет кредит");
    model1->setHeaderData(3, Qt::Horizontal, "Дата");
    model1->setHeaderData(4, Qt::Horizontal, "Сумма дебета");
    model1->setHeaderData(5, Qt::Horizontal, "Сумма кредита");

    view1->setModel(model1);
    view1->hideColumn(0);
    view1->resizeColumnsToContents();
    view1->horizontalHeader()->setStretchLastSection(true);
    view1->verticalHeader()->setStretchLastSection(true);
    view1->resize(600, 600);

    for(int i = 0; i < model1->columnCount(); ++i){
        debit1 += model1->data(model1->index(i, 3)).toInt();
        credit1 += model1->data(model1->index(i, 4)).toInt();
    }

    turnover1 = debit1 - credit1;


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

    qDebug() << turnover0 << " " << turnover1;

    //    twgt->setItem(0, 2, new QTableWidgetItem(QString(turnover0)));
//    twgt->setItem(1, 2, new QTableWidgetItem();

    vlay->addWidget(twgt);

    ui->centralWidget->setLayout(vlay);

//    db->fillDB(accounts0[0].first, accounts0[0].second, "01.05.2018", 200, db->OPERATION_TYPE::DEBIT);
//    db->fillDB(accounts0[0].first, accounts0[0].second, "01.05.2018", 200, db->OPERATION_TYPE::DEBIT);
//    db->fillDB(accounts0[0].second, accounts0[0].first, "03.05.2018", 100, db->OPERATION_TYPE::CREDIT);
//    db->fillDB(accounts0[0].second, accounts0[0].first, "03.05.2018", 100, db->OPERATION_TYPE::CREDIT);

//    db->fillDB(accounts1[0].first, accounts0[0].second, "02.05.2018", 100, db->OPERATION_TYPE::DEBIT);
//    db->fillDB(accounts1[0].first, accounts0[0].second, "02.05.2018", 100, db->OPERATION_TYPE::DEBIT);
//    db->fillDB(accounts1[0].second, accounts0[0].first, "04.05.2018", 50, db->OPERATION_TYPE::CREDIT);
//    db->fillDB(accounts1[0].second, accounts0[0].first, "04.05.2018", 100, db->OPERATION_TYPE::CREDIT);


    connect(twgt, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(item_clicked()));
}

void MainWindow::item_clicked(){

    dialogLay = new QVBoxLayout();

    if(twgt->currentIndex().row() == 0){ //отображаю первую таблицу
        view0->show();
    } else if(twgt->currentIndex().row() == 1){ //отображаю вторую таблицу
        view1->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
