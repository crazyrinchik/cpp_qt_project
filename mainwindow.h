#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void firstWindow();

// private slots:
//     void on_Upload_file_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
