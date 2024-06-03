#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tableview.h"
#include "listview.h"
#include "currency_rate.h"
#include "analysisdialog.h"
#include "ui_mainwindow.h"
#include "cashback.h"
#include "loggingcategory.h"
#include "proxymodel.h"
#include "sortdialog.h"
#include "start_page.h"
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &filename, QWidget *parent = nullptr);
    ~MainWindow();

    QSpinBox* getBudgetSpinBox() const { return ui->budgetSpinBox; }
    QPushButton* getCashBackButton() const { return ui->CashBackButton; }
    QPushButton* getTableViewButton() const { return ui->TableViewButton; }
    QPushButton* getLimitButton() const { return ui->LimitButton; }
    QPushButton* getListViewButton() const { return ui->ListViewButton; }
    QPushButton* getAnalysisButton() const { return ui->analisisButton; }

signals:
    void firstWindow();

private slots:
    void on_CashBackButton_clicked();
    void on_TableViewButton_clicked();
    void on_budgetSpinBox_valueChanged(int value);

    void on_LimitButton_clicked();

    void on_ListViewButton_clicked();

    void updatePieChart();

    void on_exchangeRateButton_clicked();

    void on_analisisButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
    int budgetLimit;
    QChartView *chartView;
    QPieSeries *series;
    CurrencyRate *rate;
    AnalysisDialog *analysisDialog;
};

#endif // MAINWINDOW_H
