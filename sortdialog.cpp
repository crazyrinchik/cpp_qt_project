#include "sortdialog.h"
#include "ui_sortdialog.h"
#include "loggingcategory.h"

SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SortDialog)
{
    ui->setupUi(this);
    setupWindow();
    qCDebug(application) << "SortDialog created";
}

SortDialog::~SortDialog()
{
    delete ui;
    qCDebug(application) << "SortDialog destroyed";
}

void SortDialog::setupWindow()
{
    setWindowTitle("Filter purchases");

    ui->comboBox->addItem("Operation Date");
    ui->comboBox->addItem("Operation Amount");
    ui->comboBox->addItem("Operation Amount with rounding");
    ui->comboBox->addItem("Cashback");
    ui->comboBox->addItem("Category");

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SortDialog::accept);
}


int SortDialog::selectedFieldIndex() const
{
    return ui->comboBox->currentIndex();
    qCDebug(application) << "SortDialog selected the index";
}

Qt::SortOrder SortDialog::sortOrder() const
{
    if (ui->ascendingRadioButton->isChecked())
        return Qt::AscendingOrder;
    else
        return Qt::DescendingOrder;
    qCDebug(application) << "SortDialog sorted the data";
}
