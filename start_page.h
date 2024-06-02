#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"
#include "tableview.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QDate>
#include <QTime>



QT_BEGIN_NAMESPACE
namespace Ui {
class Start_page;
}
QT_END_NAMESPACE

class Start_page : public QWidget
{
    Q_OBJECT

public:
    explicit Start_page(QWidget *parent = nullptr);
    ~Start_page();


private slots:
    void on_Upload_file_button_clicked();

private:
    Ui::Start_page *ui;
    QMainWindow *mainWindow;
};


#endif // START_PAGE_H


