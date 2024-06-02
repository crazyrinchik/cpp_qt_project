#ifndef CURRENCY_RATE_H
#define CURRENCY_RATE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>


namespace Ui {
class CurrencyRate;
}

class CurrencyRate : public QWidget
{
    Q_OBJECT

public:
    CurrencyRate(QWidget *parent = nullptr);
    ~CurrencyRate();

private slots:
    void onResult(QNetworkReply *reply);

private:
    Ui::CurrencyRate *ui;
    QNetworkAccessManager *networkManager;
};

#endif // CURRENCY_RATE_H
