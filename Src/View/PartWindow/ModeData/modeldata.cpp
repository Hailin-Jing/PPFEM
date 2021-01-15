#include "modeldata.h"
#include "ui_modeldata.h"
#include <QMessageBox>

ModelData::ModelData(QWidget *parent,int P) :
    QMainWindow(parent),
    ui(new Ui::ModelData)
{
    ui->setupUi(this);
    QPalette palette  = ui->plainTextEdit->palette();
    palette.setColor(QPalette::Text,QColor(100,100,100));
    ui->plainTextEdit->setPalette(palette);
    partIndex = P;
    QString fileName = QString("Mesh/PartMesh")+QString::number(partIndex+1)+QString(".d");
    QFile aFile(fileName);
    if (!aFile.exists())
    {
        QMessageBox::warning(this,"错误","网格参数文件不存在");
        return;
    }
    if (!aFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","文件打开失败");
        return;
    }
    ui->plainTextEdit->setPlainText(aFile.readAll());
}

ModelData::~ModelData()
{
    delete ui;
}


void ModelData::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}


void ModelData::on_actionSave_triggered()
{
    QString fileName = QString("Mesh/PartMesh")+QString::number(partIndex+1)+QString(".d");
    QFile aFile(fileName);
    if (!aFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","文件保存失败");
        return;
    }
    QString str = ui->plainTextEdit->toPlainText();
    QByteArray strBytes = str.toUtf8();
    aFile.write(strBytes,strBytes.length());
}
