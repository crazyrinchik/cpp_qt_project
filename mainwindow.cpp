#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    TableView *tableView = new TableView(this);
    tableView->show();
}


