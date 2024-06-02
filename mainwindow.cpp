#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

MainWindow::MainWindow(const QString &filename, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , filename(filename)
{
    ui->setupUi(this);
    setWindowTitle("Finance Master");
    connect(ui->budgetSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_budgetSpinBox_valueChanged);


    series = new QPieSeries();
    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Expenses by Category");
    chart->legend()->setAlignment(Qt::AlignRight);
    chartView->setChart(chart);

    chartView->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->chartWidget->setLayout(layout);

    updatePieChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_budgetSpinBox_valueChanged(int value)
{
    budgetLimit = value;
}

void MainWindow::on_CashBackButton_clicked()
{
    cashback *cashback_window = new cashback(filename, this);
    cashback_window->LoadData();
    cashback_window->show();
}


void MainWindow::on_TableViewButton_clicked()
{   
    TableView *tableView = new TableView(filename, this);
    tableView->show();
}


void MainWindow::on_LimitButton_clicked()
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open file!");
        return;
    }

    QTextStream stream(&file);
    QString headerLine = stream.readLine();
    QStringList headers = headerLine.split(",");

    int spendingIndex = headers.indexOf("Operation Amount with rounding");
    if (spendingIndex == -1) {
        QMessageBox::critical(this, "Error", "Operation Amount with rounding column not found!");
        file.close();
        return;
    }

    double totalSpending = 0.0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(",");
        if (fields.size() > spendingIndex) {
            bool ok;
            double value = fields[spendingIndex].toDouble(&ok);
            if (ok) {
                totalSpending += value;
            }
        }
    }

    file.close();

    if (totalSpending > budgetLimit) {
        QMessageBox::warning(this, "Budget Limit Exceeded", QString("Total spending Amount: %1 exceeds the budget limit of %2!").arg(totalSpending).arg(budgetLimit));
    } else {
        QMessageBox::information(this, "Total spending Amount", QString("Total Spending Amount: %1").arg(totalSpending));
    }
}


void MainWindow::on_ListViewButton_clicked()
{
    ListView *listView = new ListView(filename, this);
    listView->show();
}


void MainWindow::updatePieChart()
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open file!");
        return;
    }

    QTextStream stream(&file);
    QString headerLine = stream.readLine();
    QStringList headers = headerLine.split(",");

    int categoryIndex = headers.indexOf("Category");
    int expenseIndex = headers.indexOf("Operation Amount with rounding");

    if (categoryIndex == -1 || expenseIndex == -1) {
        QMessageBox::critical(this, "Error", "Required columns not found in the CSV file!");
        return;
    }

    QMap<QString, double> expensesByCategory;

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(",");

        QString category = fields.at(categoryIndex).trimmed();
        double expense = fields.at(expenseIndex).toDouble();

        expensesByCategory[category] += expense;
    }

    file.close();

    series->clear();

    for (auto it = expensesByCategory.begin(); it != expensesByCategory.end(); ++it) {
        series->append(it.key(), it.value());
    }
}


void MainWindow::on_exchangeRateButton_clicked()
{
    CurrencyRate *rate = new CurrencyRate(this);
    rate->show();
}

