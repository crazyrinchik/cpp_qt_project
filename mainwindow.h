#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "start_page.h"
#include "tableview.h"
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &filename, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void firstWindow();

private slots:
    void on_TableViewButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
};

#endif // MAINWINDOW_H
