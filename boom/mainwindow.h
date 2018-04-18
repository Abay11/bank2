#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>
#include <QDialog>
#include <QTableWidget>
#include <QSqlQueryModel>
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

private:
    Ui::MainWindow *ui;
    QPushButton *button;
    QVBoxLayout *vlay;
    QDialog *dialog;
    QTableView *view0, *view1;
    QTableWidget *twgt;
    DB *db;
    std::vector<std::pair<QString, QString>> accounts0, accounts1;
};

#endif // MAINWINDOW_H
