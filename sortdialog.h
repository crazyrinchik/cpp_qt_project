#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "proxymodel.h"

namespace Ui {
class SortDialog;
}

class SortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SortDialog(QWidget *parent = nullptr);
    ~SortDialog();

    int selectedFieldIndex() const;
    Qt::SortOrder sortOrder() const;

private:
    Ui::SortDialog *ui;

    void setupWindow();
};

#endif // SORTDIALOG_H
