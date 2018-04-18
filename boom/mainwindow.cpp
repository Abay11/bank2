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

    twgt->verticalHeader()->hide();
    twgt->horizontalHeader()->setStretchLastSection(true);
    twgt->setColumnCount(4);
    twgt->setRowCount(3);
    QStringList list;
    list.push_back("Наименование\nпоказателя");
    list.push_back("Истоичник\nинформации");
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


    vlay->addWidget(twgt);


    ui->centralWidget->setLayout(vlay);

    accounts0.push_back(std::make_pair<QString, QString>("70601810500002710404", "40817810900000003333"));
    accounts0.push_back(std::make_pair<QString, QString>("70601810500012710404", "40817810900000013333"));
    accounts1.push_back(std::make_pair<QString, QString>("70601810900002720405", "40817810900000023333"));
    accounts1.push_back(std::make_pair<QString, QString>("70601810900102720405", "40817810900000033333"));

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
    QVBoxLayout *vlay = new QVBoxLayout();

    //vlay.addWidget();
    dialog->setLayout(vlay);
    dialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
