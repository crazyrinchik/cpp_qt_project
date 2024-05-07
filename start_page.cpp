#include "start_page.h"
#include "ui_start_page.h"
#include "mainwindow.h"


#include <QFileDialog>
#include <QTextStream>

Start_page::Start_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Start_page)
{
    ui->setupUi(this);

    mainWindow = new MainWindow();
    connect(mainWindow, &MainWindow::firstWindow, this, &Start_page::show);
}

Start_page::~Start_page()
{
    delete ui;
}

void Start_page::on_Upload_file_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QObject::tr("Open File"), "",
                                                    QObject::tr("All Files (*)"));

    if (fileName.isEmpty()) {
        qDebug() << "No file selected!";
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file!";
        } else {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                qDebug() << line;
            }
        }
    }

    mainWindow->show();
    this->close();

}

