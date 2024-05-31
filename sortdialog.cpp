#include "sortdialog.h"
#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SortDialog)
{
    ui->setupUi(this);
    setupWindow();
}

SortDialog::~SortDialog()
{
    delete ui;
}

void SortDialog::setupWindow()
{
    setWindowTitle("Filter purchases");

    ui->comboBox->addItem("Operation Date");
    ui->comboBox->addItem("Operation Amount");
    ui->comboBox->addItem("Operation Amount with rounding");
    ui->comboBox->addItem("Category");

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SortDialog::accept);
}

int SortDialog::selectedFieldIndex() const
{
    return ui->comboBox->currentIndex();
}

Qt::SortOrder SortDialog::sortOrder() const
{
    if (ui->ascendingRadioButton->isChecked())
        return Qt::AscendingOrder;
    else
        return Qt::DescendingOrder;
}
