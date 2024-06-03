#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QDialog>
#include <QStandardItemModel>
#include <QFile>
#include <QMessageBox>
#include <QSortFilterProxyModel>


namespace Ui {
class TableView;
}

class TableView : public QDialog
{
    Q_OBJECT

public:
    explicit TableView(const QString &filename, QWidget *parent = nullptr);
    ~TableView();

private:
    Ui::TableView *ui;
    QString filename;
    void loadDataset();
    void setupWindow();
    void SearchInTableView(const QString& searchText);

private slots:
    void on_filterButton_clicked();
};

#endif // TABLEVIEW_H
