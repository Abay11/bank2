#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>
#include <QDialog>
#include <QTableWidget>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <vector>
#include <db.h>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void item_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void make_table(QString account);

private:
    Ui::MainWindow *ui;
    QPushButton *button;
    QVBoxLayout *vlay;
    QDialog *dialog;
    QTableView *view0, *view1;
    QTableWidget *twgt;
    QSqlQueryModel *model0, *model1;
    DB *db;
    std::vector<std::pair<QString, QString>> accounts0, accounts1;
    QVBoxLayout *dialogLay;
    int debit0 = 0, credit0 = 0, debit1 = 0, credit1 = 0, turnover0 = 0, turnover1 = 0;
};

#endif // MAINWINDOW_H
