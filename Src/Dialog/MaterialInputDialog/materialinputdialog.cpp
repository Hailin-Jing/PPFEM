#include "materialinputdialog.h"
#include "ui_materialinputdialog.h"

MaterialInputDialog::MaterialInputDialog(QWidget *parent,QString materialName) :
    QDialog(parent),
    ui(new Ui::MaterialInputDialog)
{
    ui->setupUi(this);
    ui->MaterialName->setText(materialName);
}

MaterialInputDialog::~MaterialInputDialog()
{
    delete ui;
}

double MaterialInputDialog::Modulus()
{
    return ui->modulus->value();
}

double MaterialInputDialog::PossionsRatio()
{
    return ui->possionsRatio->value();
}

double MaterialInputDialog::Density()
{
    return ui->density->value();
}

QString MaterialInputDialog::MaterialName()
{
    return ui->MaterialName->text();
}
