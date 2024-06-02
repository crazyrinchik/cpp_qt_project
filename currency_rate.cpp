#include "currency_rate.h"
#include "ui_currency_rate.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>

CurrencyRate::CurrencyRate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrencyRate)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &CurrencyRate::onResult);

    networkManager->get(QNetworkRequest(QUrl("https://open.er-api.com/v6/latest/RUB")));
}

CurrencyRate::~CurrencyRate()
{
    delete ui;
}

void CurrencyRate::onResult(QNetworkReply *reply)
{
    if(!reply->error()){
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

        QJsonObject root = document.object();
        ui->textEdit->append("Base currency: " + root.value("base_code").toString());
        QJsonObject rates = root.value("rates").toObject();

        for(auto it = rates.begin(); it != rates.end(); ++it){
            QString currency = it.key();
            double value = it.value().toDouble();
            ui->textEdit->append(currency + ": " + QString::number(value));
        }
    }
    reply->deleteLater();
}
