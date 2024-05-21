#include "start_page.h"
#include "ui_start_page.h"
#include "mainwindow.h"


#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <qDebug>
#include <QPixmap>

Start_page::Start_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Start_page)
{
    ui->setupUi(this);

    QPixmap pix(":/img/_17fc8ee5-7037-4e75-9cf4-348f010e09c0.jpeg");
    int width = ui -> image -> width();
    int height = ui -> image -> height();

    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));

    mainWindow = new MainWindow();
    connect(mainWindow, &MainWindow::firstWindow, this, &Start_page::show);
}

Start_page::~Start_page()
{
    delete ui;
}

void Start_page::on_Upload_file_button_clicked()
{
    std::vector<Data> data;
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QObject::tr("Open File"), "",
                                                    QObject::tr("CSV Files (*.csv)"));
    QFile file(fileName);
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    if (fileName.isEmpty()) {
        QMessageBox::critical(this, "Error", "No file selected!");
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Failed to open file!");
        } else {
            QTextStream in(&file);
            QString lines = in.readLine();
            while (!in.atEnd()) {
                lines = in.readLine();
                QStringList line = lines.split(';');
                Data transaction;
                QString dateTime = line[0];
                int spacePosition = dateTime.indexOf(' ');
                QString time = dateTime.mid(spacePosition + 1);
                transaction.time = time;
                transaction.paymentDate = line[1];
                transaction.cardNumber = line[2];
                transaction.paymentStatus = line[3];
                transaction.transactionAmount = line[4].toDouble();
                transaction.transactionCurrency = line[5];
                transaction.paymentAmount = line[6].toDouble();
                transaction.paymentCurrency = line[7];
                transaction.cashback = line[8].toDouble();
                transaction.category = line[9];
                transaction.mcc = line[10];
                transaction.description = line[11];
                transaction.bonuses = line[12].toDouble();
                transaction.rounding = line[13].toDouble();
                transaction.roundedTransactionAmount = line[14].toDouble();
                data.push_back(transaction);
            }
            file.close();
            for (const auto& transaction : data) {
                qDebug() << "Time:" << transaction.time
                         << "PaymentDate:" << transaction.paymentDate
                         << "CardNumber:" << transaction.cardNumber
                         << "PaymentStatus:" << transaction.paymentStatus
                         << "TransactionAmount:" << transaction.transactionAmount
                         << "TransactionCurrency:" << transaction.transactionCurrency
                         << "PaymentAmount:" << transaction.paymentAmount
                         << "PaymentCurrency:" << transaction.paymentCurrency
                         << "Cashback:" << transaction.cashback
                         << "Category:" << transaction.category
                         << "MCC:" << transaction.mcc
                         << "Description:" << transaction.description
                         << "Bonuses:" << transaction.bonuses
                         << "Rounding:" << transaction.rounding
                         << "RoundedTransactionAmount:" << transaction.roundedTransactionAmount;
            }
            mainWindow->show();
            this->close();
        }
    }
}

