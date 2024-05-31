#include "listview.h"
#include "ui_listview.h"

ListView::ListView(const QString &filename, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListView)
    , model(new QStandardItemModel(this))
    , filename(filename)
{
    ui->setupUi(this);
    ui->listView->setModel(model);

    loadData();
}

ListView::~ListView()
{
    delete ui;
}

void ListView::loadData()
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
    int cashbackIndex = headers.indexOf("Cashback");
    int expenseIndex = headers.indexOf("Operation Amount with rounding");


    if (categoryIndex == -1 || cashbackIndex == -1 || expenseIndex == -1) {
        QMessageBox::critical(this, "Error", "Required columns not found in the CSV file!");
        return;
    }

    QMap<QString, double> totalCashback;
    QMap<QString, double> totalExpenses;

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(",");

        QString category = fields.at(categoryIndex);
        double cashback = fields.at(cashbackIndex).toDouble();
        double expense = fields.at(expenseIndex).toDouble();

        totalCashback[category] += cashback;
        totalExpenses[category] += expense;
    }

    file.close();

    for (auto it = totalCashback.begin(); it != totalCashback.end(); ++it) {
        QString category = it.key();
        double cashback = it.value();
        double expense = totalExpenses[category];

        QString displayData = QString("Card Number: %1 | Total Cashback: %2 | Total Expense: %3")
                                  .arg(category)
                                  .arg(cashback)
                                  .arg(expense);

        QStandardItem *item = new QStandardItem(displayData);
        model->appendRow(item);
    }
}

