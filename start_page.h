#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QtSql>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <mainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Start_page;
}
QT_END_NAMESPACE

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
};
#endif // START_PAGE_H
