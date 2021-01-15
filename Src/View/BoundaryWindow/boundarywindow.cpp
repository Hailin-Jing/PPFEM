#include "boundarywindow.h"
#include "ui_boundarywindow.h"

//BoundaryConditionDialog Headers
#include "boundaryconditiondialog.h"
#include "ui_boundaryconditiondialog.h"

//LoadDialog Headers
#include "loaddialog.h"
#include "ui_loaddialog.h"

BoundaryWindow::BoundaryWindow
(QWidget *parent, Model *model, DXFFilter *DXF, int partIndex,int windowType) :
    QMainWindow(parent),
    ui(new Ui::BoundaryWindow)
{
    ui->setupUi(this);
    this->model = model;
    this->partIndex = partIndex;
    labXYVaulue = new QLabel("X= ,Y=");
    labXYVaulue->setMinimumWidth(200);
    ui->statusbar->addWidget(labXYVaulue);
    QObject::connect(ui->chartView,SIGNAL(mouseMovePoint(QPoint)),
                     this,SLOT(on_mouseMovePoint(QPoint)));
    this->DXF = DXF;
    this->CPI = DXF->getCPI(2);
    this->CPI = DXF->getCPI(2);
    this->PR = DXF->getPrimitives();

    //初始化坐标区
    std::vector<int> P;
    P.resize(1);
    for (int i = 0; i < int(PR.size()); i++)
    {
        P[0] = i;
        SPI.push_back(P);
    }
    std::vector<double> range = DXF->getRange();
    ui->chartView->iniChartView(PR,SPI,range);

    //初始化窗口
    switch (windowType) {
    case 1:
        ui->toolBar->removeAction(ui->actionAddLoad);break;
    case 2:
        ui->toolBar->removeAction(ui->actionAddBoundaryCondition);break;
    }
}

BoundaryWindow::~BoundaryWindow()
{
    delete ui;
}

void BoundaryWindow::on_mouseMovePoint(QPoint point)
{
    QPointF pt = ui->chartView->chart()->mapToValue(point);
    labXYVaulue->setText(QString::asprintf("坐标：X=%.1f,Y=%.2f",pt.x(),pt.y()));
}

void BoundaryWindow::on_actionZoomIn_triggered()
{
    ui->chartView->chart()->zoom(1.2);
    ui->chartView->setZoomFactor(ui->chartView->getZoomFactor()*1.2);
}

void BoundaryWindow::on_actionZoomOut_triggered()
{
    ui->chartView->chart()->zoom(0.8);
    ui->chartView->setZoomFactor(ui->chartView->getZoomFactor()*0.8);
}

void BoundaryWindow::on_actionZoomReset_triggered()
{
    ui->chartView->chart()->zoomReset();
    ui->chartView->setZoomFactor(1);
}

void BoundaryWindow::on_actionChooseBoundary_triggered()
{
    ui->chartView->setChooseMode(1);
}

void BoundaryWindow::on_actionCancelSelect_triggered()
{
    if (ui->actionCancelSelect->isChecked())
        ui->chartView->setChooseMode(2);
    else
        ui->chartView->setChooseMode(1);
}

void BoundaryWindow::on_actionReSelect_triggered()
{
    ui->chartView->iniLineSeriesColor();
}

void BoundaryWindow::on_actionAddBoundaryCondition_triggered()
{
    BoundaryConditionDialog *dialog = new BoundaryConditionDialog(this);
    int ret = dialog->exec();
    if (ret == QDialog::Rejected)
    {
        QMessageBox::warning(this,"失败","未添加任何约束");
        return;
    }
    bool DegreeConstraintX = dialog->getConstraintX();
    bool DegreeConstraintY = dialog->getConstraintY();
    double MinRange = dialog->getMinRange();
    double MaxRange = dialog->getMaxRange();
    if (MinRange > MaxRange)
    {
        QMessageBox::information(this,"失败","边界范围输入错误");
        return;
    }
    std::vector<int> CP = ui->chartView->getChosenPrimitive();
    for (unsigned int i = 0; i < CP.size(); i++)
    {
//        std::vector<double> NewBoundaryCondition;
//        NewBoundaryCondition.push_back(model->getPart(partIndex)->BC.size());
//        NewBoundaryCondition.push_back(CP[i]);
//        NewBoundaryCondition.push_back(MinRange);
//        NewBoundaryCondition.push_back(MaxRange);
//        NewBoundaryCondition.push_back(double(DegreeConstraintX));
//        NewBoundaryCondition.push_back(double(DegreeConstraintY));
        int BCIndex = int(model->getPart(partIndex)->BC.size());
        BC BC(BCIndex,CP[i],MinRange,MaxRange,DegreeConstraintX,DegreeConstraintY);
        model->getPart(partIndex)->BC.push_back(BC);
//        model->getPart(partIndex)->BC.push_back(NewBoundaryCondition);
        model->addBoundaryConditionNumber();
    }
    QMessageBox::information(this,"成功","边界条件添加成功");
    delete dialog;
}

void BoundaryWindow::on_actionAddLoad_triggered()
{

    LoadDialog *dialog = new LoadDialog(this);
    int ret = dialog->exec();
    int LoadType = -1;
    double BPX = 0, BPY = 0, EPX = 0, EPY = 0;
    double MinRange = 0, MaxRange = 1;
    if (ret == QDialog::Rejected)
    {
        QMessageBox::warning(this,"失败","未添加任何荷载");
        return;
    }
    LoadType = dialog->getLoadType();
    BPX = dialog->getBPX();
    BPY = dialog->getBPY();
    EPX = dialog->getEPX();
    EPY = dialog->getEPY();
    MinRange = dialog->getMinRange();
    MaxRange = dialog->getMaxRange();
    if (MinRange > MaxRange)
    {
        QMessageBox::information(this,"失败","边界范围输入错误");
        return;
    }
    std::vector<int> CP = ui->chartView->getChosenPrimitive();
    for (unsigned int i = 0; i < CP.size(); i++)
    {
//        std::vector<double> NewLoad;
//        NewLoad.push_back(model->getPart(partIndex)->F.size());
//        NewLoad.push_back(LoadType);
//        NewLoad.push_back(CP[i]);
//        NewLoad.push_back(MinRange);
//        NewLoad.push_back(MaxRange);
//        NewLoad.push_back(BPX);
//        NewLoad.push_back(BPY);
//        NewLoad.push_back(EPX);
//        NewLoad.push_back(EPY);
        int LoadIndex = int(model->getPart(partIndex)->F.size());
        LOAD F(LoadIndex,LoadType,CP[i],MinRange,MaxRange,BPX,BPY,EPX,EPY);
        model->getPart(partIndex)->F.push_back(F);
        model->addLoadNumber();
    }
    QMessageBox::information(this,"成功","添加荷载成功");
    delete dialog;
}
