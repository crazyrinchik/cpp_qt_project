#include "start_page.h"
#include "ui_start_page.h"
#include "loggingcategory.h"


Start_page::Start_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Start_page)
{
    ui->setupUi(this);

    QPixmap pix(":/img/_17fc8ee5-7037-4e75-9cf4-348f010e09c0.jpeg");
    int width = ui -> image -> width();
    int height = ui -> image -> height();

    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
    qCDebug(application) << "StartPage created";
}

Start_page::~Start_page()
{
    delete ui;
    qCDebug(application) << "StartPage destroyed";
}

void Start_page::on_Upload_file_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QObject::tr("Open File"), "",
                                                    QObject::tr("CSV Files (*.csv)"));
    fileName = QDir::toNativeSeparators(fileName);

    if (fileName.isEmpty()) {
        QMessageBox::critical(this, "Error", "No file selected!");
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open file!");
        return;
    }


    MainWindow *mainWindow = new MainWindow(fileName);
    connect(mainWindow, &MainWindow::firstWindow, this, &Start_page::show);
    file.close();
    mainWindow->show();
    this->close();
    qCDebug(application) << "StartPage load the filepath and closed";
}
