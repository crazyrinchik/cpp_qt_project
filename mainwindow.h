#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "start_page.h"
#include "tableview.h"
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void firstWindow();

private slots:
    void on_TableViewButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
