#ifndef CASHBACK_H
#define CASHBACK_H

#include <QDialog>
#include <QLabel>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>


namespace Ui {
class cashback;
}

class cashback : public QDialog
{
    Q_OBJECT

public:
    ~cashback();
    void LoadData();
    explicit cashback(QString &filename, QWidget *parent = nullptr);


private:
    Ui::cashback *ui;
    QLabel *cashback_amount;
    QString filename;
    double totalCashback;
};

#endif // CASHBACK_H
