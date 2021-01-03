#include "mainwindow.h"
#include "ui_mainwindow.h"

//PartWindow Headers
#include "partinputdialog.h"
#include "ui_partinputdialog.h"
#include "dxffilter.h"
#include "dxflib/src/dl_dxf.h"
#include "partwindow.h"
#include "ui_partwindow.h"

//MaterialDialog Headers
#include "materialinputdialog.h"
#include "ui_materialinputdialog.h"

//PartChooseDialog Headers
#include "partchoosedialog.h"
#include "ui_partchoosedialog.h"

//BoundaryWindow Headers
#include "boundarywindow.h"
#include "ui_boundarywindow.h"

//NewLoadDialog Headers
#include "newloaddialog.h"
#include "ui_newloaddialog.h"

//Manager Headers
#include "manager.h"
#include "ui_manager.h"

//JobDialog Headers
#include "jobdialog.h"
#include "ui_jobdialog.h"

//DataVisualization Headers
#include "datavisualization.h"
#include "ui_datavisualization.h"

//Open VTK File Headers
#include "windows.h"
#include "shellapi.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent,int argc,char **argv) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->argc = argc;
    this->argv = argv;
    this->setWindowState(Qt::WindowMaximized);
    ui->tabWidget->clear();
    model = new Model;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createManager
(QString title, QStringList headerText,std::vector<std::vector<QString> > data,std::vector<bool> editable)
{
    QStandardItemModel *theModel = new QStandardItemModel(this);
    QItemSelectionModel *theSelection = new QItemSelectionModel(theModel);

    //写入表头数据
    QStandardItem *headerItem;
    theModel->setColumnCount(headerText.count());
    theModel->setHorizontalHeaderLabels(headerText);

    for (int i = 0; i < theModel->columnCount(); i++)
    {
        headerItem = new QStandardItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setFamily("Times New Roman");
        font.setPointSize(12);
        headerItem->setFont(font);
        theModel->setHorizontalHeaderItem(i, headerItem);
    }

    //写入表项数据
    QStandardItem *aItem;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        for (unsigned int j = 0; j < unsigned(headerText.count()); j++)
        {
            aItem = new QStandardItem(data[i][j]);
            aItem->setTextAlignment(Qt::AlignCenter);
            aItem->setEditable(editable[j]);  //1111111
            QFont font = aItem->font();
            font.setFamily("Times New Roman");
            font.setPointSize(12);
            aItem->setFont(font);
            theModel->setItem(int(i),int(j),aItem);
        }
    }

    Manager *manager = new Manager(this,model,theModel,theSelection,title,headerText,data,this);
    manager->setWindowTitle(title);
    manager->setAttribute(Qt::WA_DeleteOnClose);
    manager->setWindowFlag(Qt::Window,true);
    manager->show();
}

void MainWindow::NewMaterial()
{
    on_actionNewMaterial_triggered();
}

void MainWindow::NewPart()
{
    on_actionNewPart_triggered();
}

void MainWindow::NewBoundaryCondition()
{
    on_actionNewBoundaryCondition_triggered();
}

void MainWindow::NewLoad()
{
    on_actionNewLoad_triggered();
}

//void MainWindow::TrigularElement3To6(int PI)
//{
//    int ElementNumber = model->getElementNumber();
//    int NodeNumber = model->getNodeNumber();
//    int SideNumber = model->getPart(PI)->NS;
//    MatrixXi ElementNode = model->getElementNode();
//    MatrixXd NodeCoordinate = model->getNodeCoordinate();
//    MatrixXi NewElementNode = ElementNode;
//    MatrixXd NewNodeCoordinate = NodeCoordinate;
//    NewElementNode.resize(ElementNumber,6);
//    NewElementNode.resize(NodeNumber+SideNumber,2);

//    int *SideChosenNode = new int[SideNumber]();
//    int NodeIndex = 0;
//    int SideIndex,iNode,jNode;
//    double ix,iy,jx,jy;
//    for (int i = 0; i < ElementNumber; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            SideIndex = ElementNode(i,j+3);
//            if (SideChosenNode[SideIndex] > 0)
//            {
//                NewElementNode(i,j+3) = SideChosenNode[SideIndex];
//                continue;
//            }
//            NewElementNode(i,j+3) = NodeNumber + NodeIndex;
//            iNode = ElementNode(i,j);
//            jNode = ElementNode(i,(j+1)%3);
//            ix = NodeCoordinate(iNode,0);
//            iy = NodeCoordinate(iNode,1);
//            jx = NodeCoordinate(jNode,0);
//            jy = NodeCoordinate(jNode,1);
//            NewNodeCoordinate(NodeNumber+NodeIndex,0) = (ix + jx) / 2;
//            NewNodeCoordinate(NodeNumber+NodeIndex,1) = (iy + jy) / 2;
//            NodeIndex++;
//            SideChosenNode[SideIndex] = NodeNumber + NodeIndex;
//        }
//    }
//    model->setNodeCoordinate(NewNodeCoordinate);
//    model->setElementNode(NewElementNode);
//    NodeNumber+=SideNumber;
//    model->setNodeNumber(NodeNumber);
//}

void MainWindow::on_actionNewPart_triggered()
{
    QString partName = QString("部件")+
            QString::number(model->getPartNumber()+1);
    partInputDialog *dialog = new partInputDialog(this,partName);

    Part Newpart(partName);

    int ret = dialog->exec();

    partName = dialog->PartName();
    QString ModelFileName = dialog->getModelFileName();

    if (ret == QDialog::Rejected)
        return;

    DXFFilter *DXF = new DXFFilter();
    DL_Dxf *dxf = new DL_Dxf();

    if (!dxf->in(ModelFileName.toStdString(),DXF))
    {
        std::cout<<ModelFileName.toStdString()<< "could not be opened.\n";
        return;
    }
    delete dxf;
    delete dialog;

    std::cout<<"File Open Successfully"<<std::endl;

    PartWindow *partWindow = new PartWindow(
                this,model,DXF,model->getPartNumber(),argc,argv);

    Newpart.DXF = DXF;
    model->addPart(Newpart);
    int cur = ui->tabWidget->addTab(partWindow,partName);

    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_actionNewMaterial_triggered()
{
    QString materialName = QString("材料")+
            QString::number(model->getMaterialNumber()+1);
    MaterialInputDialog *dialog = new MaterialInputDialog(this,materialName);

    int ret = dialog->exec();

    materialName = dialog->MaterialName();
    double Modulus = dialog->Modulus();
    double PossionsRatio = dialog->PossionsRatio();
    double Density = dialog->Density();

    if (ret == QDialog::Rejected)
        return;

    Material NewMaterial(materialName,Modulus,PossionsRatio,Density);
    model->addMaterial(NewMaterial);
}

void MainWindow::on_actionNewBoundaryCondition_triggered()
{
    if (model->getPartNumber() == 0)
    {
        QMessageBox::information(this,"提醒","请先定义部件");
        return;
    }
    int partIndex = 0;
    QStringList *list = new QStringList();
    for (int i = 0; i < model->getPartNumber(); i++)
        list->append(model->getPart(i)->PN);
    PartChooseDialog *dialog = new PartChooseDialog(this,list,model->getPartNumber());
    int ret = dialog->exec();
    if (ret == QDialog::Accepted)
        partIndex = dialog->getPartIndex();
    else
        return;
    delete dialog;

    if (model->getPart(partIndex)->NN ==0 ||
        model->getPart(partIndex)->NE == 0)
    {
        QMessageBox::information(this,"提醒","请先进行网格划分");
        return;
    }

    //窗口是否已经建立
    QString windowName = QString("创建边界条件_")+model->getPart(partIndex)->PN;
    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        if (ui->tabWidget->tabText(i) == windowName)
        {
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }

    DXFFilter *DXF = model->getPart(partIndex)->DXF;
    BoundaryWindow *boundaryConditionWindow =
            new BoundaryWindow(this,model,DXF,partIndex,1);

    int cur = ui->tabWidget->addTab(boundaryConditionWindow,windowName);
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);

}

void MainWindow::on_actionNewLoad_triggered()
{
    if (model->getPartNumber() == 0)
    {
        QMessageBox::information(this,"提醒","请先定义部件");
        return;
    }
    QStringList *list = new QStringList();
    for (int i = 0; i < model->getPartNumber(); i++)
        list->append(model->getPart(i)->PN);
    NewLoadDialog *dialog = new NewLoadDialog(this,list,model->getPartNumber());
    int ret = dialog->exec();
    if (ret == QDialog::Rejected)
        return;
    int loadType = dialog->getLoadType();
    int partIndex = dialog->getPartIndex();
    if (loadType == 1)  //自重荷载
    {
        double GX = dialog->getGX();
        double GY = dialog->getGY();
//        std::vector<double> NewLoad;
//        NewLoad.push_back(model->getPart(partIndex)->F.size());
//        NewLoad.push_back(1);
//        NewLoad.push_back(GX);
//        NewLoad.push_back(GY);
        int LoadIndex = int(model->getPart(partIndex)->F.size());
        LOAD F(LoadIndex,1,-1,-1,-1,GX,GY,-1,-1);
        model->getPart(partIndex)->F.push_back(F);
        QMessageBox::information(this,"成功","自重荷载添加成功");
        return;
    }
    delete dialog;

    QString windowName = QString("创建荷载_")+model->getPart(partIndex)->PN;
    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        if (ui->tabWidget->tabText(i) == windowName)
        {
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }

    DXFFilter *DXF = model->getPart(partIndex)->DXF;
    BoundaryWindow *boundaryConditionWindow =
            new BoundaryWindow(this,model,DXF,partIndex,2);

    int cur = ui->tabWidget->addTab(boundaryConditionWindow,windowName);
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_actionPartManager_triggered()
{
    QString title = "部件管理器";
    QStringList headerText;
    std::vector<bool> editable = {true,false,false,false,false,false};
    headerText<<"部件名"<<"图元数"<<"孔洞数"<<"结点数"<<"单元数"<<"边数";
    std::vector<std::vector<QString>> data;
    data.resize(unsigned(model->getPartNumber()));
    for (unsigned int i = 0; i < unsigned(model->getPartNumber()); i++)
    {
        Part *part = model->getPart(int(i));
        data[i].push_back(part->PN);
        data[i].push_back(QString::number(part->DXF->getPrimitives().size()));
        data[i].push_back(QString::number(part->NH));
        data[i].push_back(QString::number(part->NN));
        data[i].push_back(QString::number(part->NE));
        data[i].push_back(QString::number(part->NS));
    }
    createManager(title,headerText,data,editable);
}

void MainWindow::on_actionMaterialManager_triggered()
{
    QString title = "材料属性管理器";
    QStringList headerText;
    std::vector<bool> editable = {true,true,true,true};
    headerText<<"材料名"<<"弹性模量"<<"泊松比"<<"密度";
    std::vector<std::vector<QString>> data;
    data.resize(unsigned(model->getMaterialNumber()));
    for (unsigned int i = 0; i < unsigned(model->getMaterialNumber()); i++)
    {
        Material *material = model->getMaterial(int(i));
        data[i].push_back(material->MN);
        data[i].push_back(QString::number(material->E));
        data[i].push_back(QString::number(material->ANU));
        data[i].push_back(QString::number(material->Density));
    }
    createManager(title,headerText,data,editable);
}

void MainWindow::on_actionBoundaryConditionManager_triggered()
{
    QString title = "边界条件管理器";
    QStringList headerText;
    std::vector<bool> editable = {false,false,true,true,true,true,true};
    headerText<<"所属部件"<<"边界号"<<"图元号"<<"作用范围-起点"<<"作用范围-终点"<<"约束-X"<<"约束-Y";
    std::vector<std::vector<QString>> data;
    for (unsigned int i = 0; i < unsigned(model->getPartNumber()); i++)
    {
        Part *part = model->getPart(int(i));
        std::vector<BC> BC = part->BC;
        for (unsigned int j = 0; j < BC.size(); j++)
        {
            std::vector<QString> tempData;
            tempData.push_back(part->PN);
            tempData.push_back(QString::number(BC[j].BCIndex));
            tempData.push_back(QString::number(BC[j].PRIndex));
            tempData.push_back(QString::number(BC[j].MinRange));
            tempData.push_back(QString::number(BC[j].MaxRange));
            tempData.push_back(QString::number(BC[j].DegreeConstraintX));
            tempData.push_back(QString::number(BC[j].DegreeConstraintY));
            data.push_back(tempData);
        }
    }
    createManager(title,headerText,data,editable);
}

void MainWindow::on_actionLoadManager_triggered()
{
    QString title = "荷载管理器";
    QStringList headerText;
    std::vector<bool> editable = {false,false,false,true,true,true,true,true,true,true};
    headerText<<"所属部件"<<"荷载号"<<"荷载类型"<<"图元号"<<"作用范围-起点"
              <<"作用范围-终点"<<"G-X/q-x1"<<"G-Y/q-y1"<<"q-x2"<<"q-y2";
    std::vector<std::vector<QString>> data;
    for (unsigned int i = 0; i < unsigned(model->getPartNumber()); i++)
    {
        Part *part = model->getPart(int(i));
        std::vector<LOAD> Load = part->F;
        for (unsigned int j = 0; j < Load.size(); j++)
        {
            std::vector<QString> tempData;
            tempData.push_back(part->PN);
            if (Load[j].LoadType == 1)
            {
                tempData.push_back(QString::number(Load[j].LoadIndex));
                tempData.push_back("自重荷载");
                tempData.push_back("");
                tempData.push_back("");
                tempData.push_back("");
                tempData.push_back(QString::number(Load[j].BPX));
                tempData.push_back(QString::number(Load[j].BPY));
                tempData.push_back("");
                tempData.push_back("");
            }
            else
            {
                tempData.push_back(QString::number(Load[j].LoadIndex));
                tempData.push_back("边界分布荷载");
                tempData.push_back(QString::number(Load[j].PRIndex));
                tempData.push_back(QString::number(Load[j].MinRange));
                tempData.push_back(QString::number(Load[j].MaxRange));
                tempData.push_back(QString::number(Load[j].BPX));
                tempData.push_back(QString::number(Load[j].BPY));
                tempData.push_back(QString::number(Load[j].EPX));
                tempData.push_back(QString::number(Load[j].EPY));
            }
            data.push_back(tempData);
        }
    }
    createManager(title,headerText,data,editable);
}

void MainWindow::on_actionJob_triggered()
{

    if (model->getPartNumber()==0 || model->getMaterialNumber() == 0)
    {
        QMessageBox::warning(this,"错误","请先定义部件和材料");
        return;
    }

    JobDialog *dialog = new JobDialog(this,model);

    int ret = dialog->exec();
    if (ret == QDialog::Rejected)
        return;

    int PT = dialog->getProblemType();
    int ET = dialog->getElementType();
    double T = dialog->getThickness();
    int SM = dialog->getStorageMode();
    int SLE = dialog->getSolutionofLinearEquation();
    int PI = dialog->getPartIndex();
    int MI = dialog->getMaterialIndex();

    model->setJobArgument(PT,ET,T,SM,SLE,PI,MI);

    delete dialog;
}

void MainWindow::on_actionAnalyze_triggered()
{
    if (model->getNodeNumber() == 0
            || model->getElementNumber() == 0)
    {
        QMessageBox::warning(this,"错误","模型错误或未设置作业参数");
        return;
    }

    //int &PT, double &T, int &SM, int &SLE, int &PI, int &MI
    int PT,ET,SM,SLE,PI,MI;
    double T;
    model->getJobArgument(PT,ET,T,SM,SLE,PI,MI);

//    Part *part = model->getPart(PI);
//    int maximum = 0;
//    maximum += int(part.getBoundaryCondition().size());
//    maximum += int(part.getLoad().size());
//    maximum += model->getNodeNumber() * 2;
//    maximum += model->getElementNumber() * 2;

//    progress = new QProgressDialog(this);
//    progress->setWindowTitle("Loading");
//    progress->setLabelText("Meshing");
//    progress->setAutoClose(true);
//    progress->setRange(0,maximum);
//    progress->setWindowModality(Qt::WindowModal);
//    progress->setCancelButtonText("Cancel");
//    progress->setValue(0);
//    progress->show();

//    model->setProgressDialog(progress);

    //六节点三角形单元
    if (ET == 6)
        model->TrigularElement3To6();

    model->calcBoundaryCondition();
    model->calcLoad();

//    progress->setValue(progress->maximum());
    model->solveSystem();
    QString dlgTitle = "消息";
    QString strInfo = "计算结束";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}

void MainWindow::on_actionElementNodeNumber_triggered()
{
    //显示单元信息窗口
    MatrixXi EN = model->getElementNode();

    QStringList headerText;
    int NE = int(EN.rows());
    if (model->getElementType() == 3)
    {
        headerText<<"-i-node-"<<"-j-node-"<<"m-node";
        createDataVisualization("单元信息",headerText,EN.block(0,0,NE,3).cast<double>());
    }
    else if (model->getElementType() == 6)
    {
        headerText<<"i-Node"<<"j-Node"<<"m-Node"<<"i'-Node"<<"j'-Node"<<"m'-Node";
        createDataVisualization("单元信息",headerText,EN.block(0,0,NE,6).cast<double>());
    }
}

void MainWindow::on_actionNodeCoordinate_triggered()
{
    //显示节点信息窗口
    MatrixXd CXY = model->getNodeCoordinate();

    QStringList headerText;
    headerText<<"-X-"<<"-Y-";

    createDataVisualization("节点信息",headerText,CXY);
}

void MainWindow::on_actionFixedDegree_triggered()
{
    //显示约束自由度窗口
    VectorXi IFIX = model->getFixedDegree();
    MatrixXi CIFIX;
    CIFIX.resize(IFIX.size()/2,2);
    for (int i = 0; i < IFIX.size()/2; i++)
        for (int j = 0; j < 2; j++)
            CIFIX(i,j) = IFIX(2*i+j);

    QStringList headerText;
    headerText<<"-X-"<<"-Y-";

    createDataVisualization("约束自由度",headerText,CIFIX.cast<double>());
}

void MainWindow::on_actionLoad_triggered()
{
    //显示荷载窗口
    VectorXd Load = model->getLoad();
    MatrixXd CLoad;
    CLoad.resize(Load.size()/2,2);
    for (int i = 0; i < Load.size()/2; i++)
        for (int j = 0; j < 2; j++)
            CLoad(i,j) = Load(2*i+j);

    QStringList headerText;
    headerText<<"-X-"<<"-Y-";

    createDataVisualization("荷载",headerText,CLoad);
}

void MainWindow::on_actionID_triggered()
{
    //显示节点位移位移信息窗口
    MatrixXi ID = model->getID();

    QStringList headerText;
    headerText<<"-X-"<<"-Y-";

    createDataVisualization("节点位移信息",headerText,ID.cast<double>());
}

void MainWindow::on_actionLM_triggered()
{
    //显示连接矩阵窗口
    MatrixXi LM = model->getLM();

    QStringList headerText;
    if (model->getElementType() == 3)
        headerText<<"-I-X-"<<"-I-Y-"<<"-J-X-"<<"-J-Y-"<<"-M-X-"<<"-M-Y-";
    else if (model->getElementType() == 3)
        headerText<<"-I-X-"<<"-I-Y-"<<"-J-X-"<<"-J-Y-"<<"-M-X-"<<"-M-Y-"
                  <<"-I'-X-"<<"-I'-Y-"<<"-J'-X-"<<"-J'-Y-"<<"-M'-X-"<<"-M'-Y-";

    createDataVisualization("连接矩阵",headerText,LM.cast<double>());
}

void MainWindow::on_actionAssistentMatrix_triggered()
{
    //显示辅助数组窗口
    MatrixXi AM = model->getAM();

    QStringList headerText;
    headerText<<"1";

    createDataVisualization("辅助数组",headerText,AM.cast<double>());
}

void MainWindow::on_actionFirstNomzeroRow_triggered()
{
    //显示非零首行号窗口
    MatrixXi M = model->getM();

    QStringList headerText;
    headerText<<"1";

    createDataVisualization("非零首行号",headerText,M.cast<double>());
}

void MainWindow::createDataVisualization(QString tabName, QStringList headerText, MatrixXd data)
{
    if (data.rows() == 0)
    {
        QMessageBox::information(this,"错误","请先运行分析");
        return;
    }

    //窗口是否已经建立
    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        if (ui->tabWidget->tabText(i) == tabName)
        {
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }

    //创建DataWidget类
    DataVisualization *dataVisualization =
            new DataVisualization(headerText,data,this);

    int cur = ui->tabWidget->addTab(dataVisualization,tabName);
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_actionResult_triggered()
{
    model->createVTKResultFile();
    ShellExecuteW(nullptr,QString("open").toStdWString().c_str(),
                  (QDir::currentPath()+QString("/Result/Result.vtk"))
                  .toStdWString().c_str(),nullptr,nullptr,SW_SHOW);
}
