#ifndef ANALYSISDIALOG_H
#define ANALYSISDIALOG_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>

namespace Ui {
class AnalysisDialog;
}

class AnalysisDialog : public QDialog
{
    Q_OBJECT

public:
    AnalysisDialog(const QString &filename, QWidget *parent = nullptr);
    ~AnalysisDialog();

private:
    Ui::AnalysisDialog *ui;
    QString filename;
    QChartView *chartView;
    QLineSeries *series;

    void loadData();
    void setupChart();
};

#endif // ANALYSISDIALOG_H
