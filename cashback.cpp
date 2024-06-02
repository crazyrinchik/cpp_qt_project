#include "cashback.h"
#include "ui_cashback.h"


cashback::cashback(QString &filename, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cashback)
    , filename(filename)
    , totalCashback(0.0)
{
    ui->setupUi(this);
}

cashback::~cashback()
{
    delete ui;
}

void cashback::LoadData()
{
    QFile file(filename);
    QTextStream stream(&file);
    QString headerLine = stream.readLine();
    QStringList headers = headerLine.split(',');

    int dateIndex = headers.indexOf("Operation Date");
    int categoryIndex = headers.indexOf("Category");
    int cashbackIndex = headers.indexOf("Cashback");

    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    totalCashback = 0.0;
    int row = 0;

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.isEmpty()) {
            continue;
        }

        QStringList values = line.split(',');

        if (values.size() > cashbackIndex) {
            ui->tableWidget->insertRow(row);

            QString date = values.at(dateIndex);
            QString category = values.at(categoryIndex);
            double cashback = values.at(cashbackIndex).toDouble();

            ui->tableWidget->setItem(row, dateIndex, new QTableWidgetItem(date));
            ui->tableWidget->setItem(row, categoryIndex, new QTableWidgetItem(category));
            ui->tableWidget->setItem(row, cashbackIndex, new QTableWidgetItem(QString::number(cashback)));

            totalCashback += cashback;
            ++row;
        }
    }

    file.close();

    ui->cashback_amount->setText(QString::number(totalCashback));
    this->close();
}
