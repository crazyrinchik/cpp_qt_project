#include "cashback.h"
#include "ui_cashback.h"
#include "loggingcategory.h"


cashback::cashback(QString &filename, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cashback)
    , filename(filename)
    , totalCashback(0.0)
{
    ui->setupUi(this);
    this->LoadData();
    qCDebug(application) << "CashbackDialog created";
}

cashback::~cashback()
{
    delete ui;
    qCDebug(application) << "CashbackDialog destroyed";
}

void cashback::LoadData()
{

    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QString headerLine = stream.readLine();
    QStringList headers = {"Operation Date", "Category", "Cashback"};

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

        ui->tableWidget->insertRow(row);

        QString date = values.at(0);
        QString category = values.at(9);
        double cashback = values.at(8).toDouble();

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(date));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(category));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(cashback)));

        totalCashback += cashback;
        ++row;

    }

    file.close();

    ui->cashback_amount->setText(QString::number(totalCashback));
    this->close();
    qCDebug(application) << "CashBackDialog loaded data and created";
}
