#include "start_page.h"
#include "ui_start_page.h"
#include "mainwindow.h"


#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QPixmap>

Start_page::Start_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Start_page)
{
    ui->setupUi(this);

    QPixmap pix(":/img/_17fc8ee5-7037-4e75-9cf4-348f010e09c0.jpeg");
    int width = ui -> image -> width();
    int height = ui -> image -> height();

    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));

    mainWindow = new MainWindow();
    connect(mainWindow, &MainWindow::firstWindow, this, &Start_page::show);
}

Start_page::~Start_page()
{
    delete ui;
}

void Start_page::on_Upload_file_button_clicked()
{
    QList<QString> data;
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QObject::tr("Open File"), "",
                                                    QObject::tr("All Files (*)"));

    if (fileName.isEmpty()) {
        QMessageBox::critical(this, "Error", "No file selected!");
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Failed to open file!");
        } else {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                data.append(line);
            }
            mainWindow->show();
            this->close();
        }
    }



}
