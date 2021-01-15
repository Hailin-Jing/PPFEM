#include "loaddialog.h"
#include "ui_loaddialog.h"

LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    ui->setupUi(this);
    ui->EPX->setEnabled(false);
    ui->EPY->setEnabled(false);
}

LoadDialog::~LoadDialog()
{
    delete ui;
}


int LoadDialog::getLoadType()
{
    return ui->LoadType->currentIndex() + 2;
}

double LoadDialog::getBPX()
{
    return ui->BPX->value();
}

double LoadDialog::getBPY()
{
    return ui->BPY->value();
}

double LoadDialog::getEPX()
{
    return ui->EPX->value();
}

double LoadDialog::getEPY()
{
    return ui->EPY->value();
}

double LoadDialog::getMinRange()
{
    return ui->minRange->value();
}

double LoadDialog::getMaxRange()
{
    return ui->maxRange->value();
}


void LoadDialog::on_LoadType_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "均布荷载")
    {
        ui->BPX->setEnabled(true);
        ui->BPY->setEnabled(true);
        ui->EPX->setEnabled(false);
        ui->EPY->setEnabled(false);
    }
    else if (arg1 == "线性分布荷载")
    {
        ui->BPX->setEnabled(true);
        ui->BPY->setEnabled(true);
        ui->EPX->setEnabled(true);
        ui->EPY->setEnabled(true);
    }
}
