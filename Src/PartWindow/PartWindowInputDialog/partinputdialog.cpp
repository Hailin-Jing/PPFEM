#include "partinputdialog.h"
#include "ui_partinputdialog.h"
#include <QDir>
#include <QFileDialog>

partInputDialog::partInputDialog(QWidget *parent,QString partName) :
    QDialog(parent),
    ui(new Ui::partInputDialog)
{
    ui->setupUi(this);
    ui->PartName->setText(partName);
}

partInputDialog::~partInputDialog()
{
    delete ui;
}

QString partInputDialog::PartName()
{
    return ui->PartName->text();
}

QString partInputDialog::getModelFileName()
{
    return ui->PartModel->text();
}

void partInputDialog::on_pushButtonModel_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "打开模型文件";
    QString filter = "DXF文件(*.dxf)";
    QString ModelFileName = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (ModelFileName.isEmpty())
        return;
    ui->PartModel->setText(ModelFileName);
}
