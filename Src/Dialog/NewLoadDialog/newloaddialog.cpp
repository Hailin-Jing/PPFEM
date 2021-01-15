#include "newloaddialog.h"
#include "ui_newloaddialog.h"

NewLoadDialog::NewLoadDialog
(QWidget *parent, QStringList *partItem, int NI) :
    QDialog(parent),
    ui(new Ui::NewLoadDialog)
{
    ui->setupUi(this);
    for (int i = 0; i < NI; i++)
        ui->Part->addItem(partItem->at(i));
}

NewLoadDialog::~NewLoadDialog()
{
    delete ui;
}

int NewLoadDialog::getLoadType()
{
    int type = 0;
    if (ui->LoadType->currentText() == QString("自重荷载"))
        type = 1;
    else if (ui->LoadType->currentText() == QString("边界分布荷载"))
        type = 2;
    return type;
}

double NewLoadDialog::getGX()
{
    return ui->GX->text().toDouble();
}

double NewLoadDialog::getGY()
{
    return ui->GY->text().toDouble();
}

int NewLoadDialog::getPartIndex()
{
    return ui->Part->currentIndex();
}

void NewLoadDialog::on_LoadType_currentIndexChanged(const QString &arg1)
{
    if (arg1 == QString("自重荷载"))
    {
        ui->GX->setEnabled(true);
        ui->GY->setEnabled(true);
    }
    else if (arg1 == QString("边界分布荷载"))
    {
        ui->GX->setEnabled(false);
        ui->GY->setEnabled(false);
    }
}
