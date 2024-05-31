#include "tableview.h"
#include "ui_tableview.h"

TableView::TableView(const QString &filename, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TableView)
    , filename(filename)
{
    ui->setupUi(this);
    setupWindow();
}

TableView::~TableView()
{
    delete ui;
}

void TableView::setupWindow() {
    setWindowTitle("Table view");

    loadDataset();

    connect(ui->lineEdit, &QLineEdit::textChanged, [=](const QString& searchText) {
        SearchInTableView(searchText);
    });
}

void TableView::loadDataset(){
    QStandardItemModel* model = new QStandardItemModel(ui->tableView);

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        if (!stream.atEnd())
        {
            QString headerLine = stream.readLine();
            QStringList headers = headerLine.split(",");
            model->setHorizontalHeaderLabels(headers);
        }

        while (!stream.atEnd())
        {
            QString line = stream.readLine();

            QStringList fields;
            QString field;
            bool inQuotes = false;
            for (int i = 0; i < line.length(); ++i)
            {
                QChar c = line.at(i);
                if (c == '"')
                {
                    inQuotes = !inQuotes;
                }
                else if (c == ',' && !inQuotes)
                {
                    fields.append(field.trimmed());
                    field.clear();
                }
                else
                {
                    field.append(c);
                }
            }
            fields.append(field.trimmed());

            QList<QStandardItem*> items;

            for (const QString& field : fields)
            {
                QStandardItem* item = new QStandardItem(field);
                items.append(item);
            }

            model->appendRow(items);
        }

        file.close();
    }

    ui->tableView->setModel(model);

    ui->tableView->resizeColumnsToContents();
}

void TableView::SearchInTableView(const QString& searchText)
{
    QAbstractItemModel* model = ui->tableView->model();

    QString searchTextLower = searchText.toLower();

    for (int row = 0; row < model->rowCount(); ++row)
    {
        bool match = false;

        QModelIndex makeIndex = model->index(row, 11);
        QModelIndex modelIndex = model->index(row, 9);

        QString make = makeIndex.data(Qt::DisplayRole).toString().toLower();
        QString model = modelIndex.data(Qt::DisplayRole).toString().toLower();

        if (make.contains(searchTextLower) || model.contains(searchTextLower))
        {
            match = true;
        }

        ui->tableView->setRowHidden(row, !match);
    }
}

void TableView::on_filterButton_clicked()
{
    SortDialog sortDialog(this);
    if (sortDialog.exec() == QDialog::Accepted)
    {
        int selectedFieldIndex = sortDialog.selectedFieldIndex();
        Qt::SortOrder sortOrder = sortDialog.sortOrder();

        QAbstractItemModel* originalModel = ui->tableView->model();

        ProxyModel* proxyModel = new ProxyModel(this);
        proxyModel->setSourceModel(originalModel);

        proxyModel->setSortRole(Qt::DisplayRole);
        proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->sort(selectedFieldIndex, sortOrder);

        ui->tableView->setModel(proxyModel);
    }
}


