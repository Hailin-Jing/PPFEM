#include "jobdialog.h"
#include "ui_jobdialog.h"

JobDialog::JobDialog(QWidget *parent,Model *model) :
    QDialog(parent),
    ui(new Ui::JobDialog)
{
    ui->setupUi(this);
    for (int i = 0; i < model->getPartNumber(); i++)
        ui->Part->addItem(model->getPart(i)->PN);
    for (int i = 0; i < model->getMaterialNumber(); i++)
        ui->Material->addItem(model->getMaterial(i)->MN);
}

JobDialog::~JobDialog()
{
    delete ui;
}

int JobDialog::getProblemType()
{
    return ui->ProblemType->currentIndex();
}

int JobDialog::getElementType()
{
    int ET = 3;
    if (ui->ElementType->currentIndex() == 0)
        ET = 3;
    else if (ui->ElementType->currentIndex() == 1)
        ET = 6;
    return ET;
}

double JobDialog::getThickness()
{
    return ui->Thickness->text().toDouble();
}

int JobDialog::getStorageMode()
{
    return ui->StorageMode->currentIndex();
}

int JobDialog::getSolutionofLinearEquation()
{
    return ui->Solution->currentIndex();
}

int JobDialog::getPartIndex()
{
    return ui->Part->currentIndex();
}

int JobDialog::getMaterialIndex()
{
    return ui->Material->currentIndex();
}
