#include "boundaryconditiondialog.h"
#include "ui_boundaryconditiondialog.h"

BoundaryConditionDialog::BoundaryConditionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BoundaryConditionDialog)
{
    ui->setupUi(this);
}

BoundaryConditionDialog::~BoundaryConditionDialog()
{
    delete ui;
}

bool BoundaryConditionDialog::getConstraintX()
{
    return ui->checkBoxDegreeX->checkState();
}

bool BoundaryConditionDialog::getConstraintY()
{
    return ui->checkBoxDegreeY->checkState();
}

double BoundaryConditionDialog::getMinRange()
{
    return ui->MinRange->value();
}

double BoundaryConditionDialog::getMaxRange()
{
    return ui->MaxRange->value();
}
