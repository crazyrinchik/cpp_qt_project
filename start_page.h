#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QtSql>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <mainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Start_page;
}
QT_END_NAMESPACE

struct Data {
    QString time;
    QString paymentDate;
    QString cardNumber;
    QString paymentStatus;
    double transactionAmount;
    QString transactionCurrency;
    double paymentAmount;
    QString paymentCurrency;
    double cashback;
    QString category;
    QString mcc;
    QString description;
    double bonuses;
    double rounding;
    double roundedTransactionAmount;
};

class Start_page : public QWidget
{
    Q_OBJECT

public:
    Start_page(QWidget *parent = nullptr);
    ~Start_page();


private slots:
    void on_Upload_file_button_clicked();

private:
    Ui::Start_page *ui;
    MainWindow *mainWindow;
    std::vector<Data> data;
};


#endif // START_PAGE_H
