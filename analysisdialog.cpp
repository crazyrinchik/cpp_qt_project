#include "analysisdialog.h"
#include "ui_analysisdialog.h"
#include "loggingcategory.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

AnalysisDialog::AnalysisDialog(const QString &filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalysisDialog),
    filename(filename),
    series(new QLineSeries())
{
    ui->setupUi(this);

    loadData();
    setupChart();

    setMinimumSize(800, 600);
    qCDebug(application) << "AnalysisDialog created";
}

AnalysisDialog::~AnalysisDialog()
{
    delete ui;
    qCDebug(application) << "AnalysisDialog destroyed";
}

void AnalysisDialog::loadData()
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream stream(&file);
    QString headerLine = stream.readLine();
    QStringList headers = headerLine.split(",");
    int dateIndex = headers.indexOf("Payment Date");
    int amountIndex = headers.indexOf("Operation Amount with rounding");

    QMap<QDate, double> weeklyExpenses;

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(",");
        if (fields.size() > dateIndex && fields.size() > amountIndex) {
            QDate date = QDate::fromString(fields[dateIndex], "yyyy-MM-dd");
            double amount = fields[amountIndex].toDouble();

            QDate startOfWeek = date.addDays(-(date.dayOfWeek() - 1));
            weeklyExpenses[startOfWeek] += amount;
        }
    }

    file.close();

    for (auto it = weeklyExpenses.begin(); it != weeklyExpenses.end(); ++it) {
        series->append(it.key().startOfDay().toMSecsSinceEpoch(), it.value());
    }
    qCDebug(application) << "AnalysisDialog loaded data";
}

void AnalysisDialog::setupChart()
{
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Weekly Expenses");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd MMM yyyy");
    axisX->setTitleText("Week Starting");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Expenses");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);

    qCDebug(application) << "AnalysisDialog set up Chart";
}
