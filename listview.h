#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QDialog>
#include <QTextStream>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStandardItem>
#include <QListView>
#include <QString>
#include <QStandardItemModel>
#include "start_page.h"
#include "mainwindow.h"


namespace Ui {
class ListView;
}

class ListView : public QDialog
{
    Q_OBJECT

public:
    explicit ListView(const QString &filename, QWidget *parent = nullptr);
    ~ListView();

private:
    Ui::ListView *ui;
    QStandardItemModel *model;
    QString filename;
    void loadData();
};

#endif // LISTVIEW_H
