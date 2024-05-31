#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString &filename, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , filename(filename)
{
    ui->setupUi(this);
    setWindowTitle("Finance Master");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TableViewButton_clicked()
{
    TableView *tableView = new TableView(filename, this);
    tableView->show();
}



