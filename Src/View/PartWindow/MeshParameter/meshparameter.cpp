#include "meshparameter.h"
#include "ui_meshparameter.h"

MeshParameter::MeshParameter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeshParameter)
{
    ui->setupUi(this);
}

MeshParameter::~MeshParameter()
{
    delete ui;
}

double MeshParameter::getBoundaryNodes()
{
    return ui->boundaryNodes->text().toDouble();
}

double MeshParameter::getHoleNodes()
{
    return ui->holeNodes->text().toDouble();
}
