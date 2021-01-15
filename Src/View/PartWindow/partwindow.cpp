#include "partwindow.h"
#include "ui_partwindow.h"

#include "meshparameter.h"
#include "ui_meshparameter.h"

#include "modeldata.h"
#include "ui_modeldata.h"

#include "EasyMesh/Src/timer.h"
#include "EasyMesh/Src/easymesh.h"

const double Pi = 3.14159265358979323846264338328;

PartWindow::PartWindow
(QWidget *parent,Model *model,DXFFilter *DXF,int partIndex,int argc, char *argv[]) :
    QMainWindow(parent),
    ui(new Ui::PartWindow)
{
    ui->setupUi(this);
    this->model = model;
    this->argc = argc;
    this->argv = argv;
    this->partIndex = partIndex;
    labXYVaulue = new QLabel("X= ,Y=");
    labXYVaulue->setMinimumWidth(200);
    ui->statusbar->addWidget(labXYVaulue);
    QObject::connect(ui->chartView,SIGNAL(mouseMovePoint(QPoint)),
                     this,SLOT(on_mouseMovePoint(QPoint)));
    this->DXF = DXF;
    this->CPI = DXF->getCPI(2);
    this->RCPI = DXF->getCPI(2);
    this->PR = DXF->getPrimitives();

    //初始化坐标区
    for (int i = 0; i < int(CPI.size()); i++)
        SPI.push_back(CPI[unsigned(i)][0]);
    std::vector<double> range = DXF->getRange();
    ui->chartView->iniChartView(PR,SPI,range);
}

PartWindow::~PartWindow()
{
    delete ui;
}

int PartWindow::createMeshControlData(double boundaryNodes, double holeNodes)
{
    //生成网格控制参数到"currentPath/Mesh"

    int error = 0;

    QString meshControlData;
    std::vector<std::vector<double>> boundary;
    std::vector<std::vector<std::vector<double>>> hole;

    int boundaryIndex = model->getPart(partIndex)->BCPI;
    std::vector<int> holeIndex = model->getPart(partIndex)->HCPI;

    //边界及孔洞坐标信息
    boundary = createBoundaryNodes();
    hole = createHoleNodes();

    int pointsNumber = int(boundary.size());
    for (unsigned int i = 0; i < hole.size(); i++)
        pointsNumber += hole[i].size();
    int segmentsNumber = pointsNumber;

    meshControlData.append(QString("#*********\n"));
    meshControlData.append(QString("  POINTS\n"));
    meshControlData.append(QString("*********#\n\n"));

    meshControlData.append(QString::number(pointsNumber));
    meshControlData.append(" # number of points defining the boundary #\n");

    meshControlData.append("\n# boundary domain #\n");
    meshControlData.append("#-------+-----+-----+---------+--------#\n");
    meshControlData.append("# point |  x  |  y  | spacing | marker #\n");
    meshControlData.append("#-------+-----+-----+---------+--------#\n");
    int pointsIndex = 0;

    //边界点
    double boundaryLength = length(boundaryIndex);
    for (unsigned int i = 0 ;i < boundary.size(); i++)
    {
        meshControlData.append(QString::number(pointsIndex)+QString(":   "));
        meshControlData.append(QString::number(boundary[i][0])+QString("    "));
        meshControlData.append(QString::number(boundary[i][1])+QString("    "));
        meshControlData.append(QString::number(boundaryLength/boundaryNodes,'g',2)+QString("    "));
        meshControlData.append(QString::number(boundary[i][2])+QString("\n"));
        pointsIndex += 1;
    }
    //孔洞点
    for (unsigned int i = 0, k = 0; i < holeIndex.size(); i++)
    {
        if (holeIndex[i] == 0)
            continue;
        double holeLength = length((holeIndex[i]));
        meshControlData.append(QString("\n# Hole ")+QString::number(k+1)+QString("#\n"));
        meshControlData.append("#-------+-----+-----+---------+--------#\n");
        meshControlData.append("# point |  x  |  y  | spacing | marker #\n");
        meshControlData.append("#-------+-----+-----+---------+--------#\n");
        for (unsigned int j = 0; j < hole[k].size(); j++)
        {
            meshControlData.append(QString::number(pointsIndex)+QString(":   "));
            meshControlData.append(QString::number(hole[k][j][0])+QString("    "));
            meshControlData.append(QString::number(hole[k][j][1])+QString("    "));
            meshControlData.append(QString::number(holeLength/holeNodes)+QString("    "));
            meshControlData.append(QString::number(hole[k][j][2])+QString("\n"));
            pointsIndex += 1;
        }
        k++;
    }

    meshControlData.append(QString("\n\n#*********\n"));
    meshControlData.append(QString(" SEGMENTS\n"));
    meshControlData.append(QString("*********#\n\n"));

    meshControlData.append(QString::number(segmentsNumber));
    meshControlData.append(" # number of segments#\n");

    meshControlData.append("\n# boundary domain #\n");
    meshControlData.append("#---------+-------+-------+--------#\n");
    meshControlData.append("# segment |  1st  |  2nd  | marker #\n");
    meshControlData.append("#---------+-------+-------+--------#\n");
    unsigned int segmentsIndex = 0;
    //边界
    for (unsigned int i = 0;i < boundary.size(); i++)
    {
        meshControlData.append(QString::number(segmentsIndex)+QString(":   "));
        meshControlData.append(QString::number(segmentsIndex)+QString("    "));
        meshControlData.append(QString::number((segmentsIndex+1) % boundary.size())+QString("    "));
        meshControlData.append(QString::number(boundary[i][2])+QString("\n"));
        segmentsIndex += 1;
    }
    //孔洞
    for (unsigned int i = 0, k = 0; i < holeIndex.size(); i++)
    {
        if (holeIndex[i] == 0)
            continue;
        meshControlData.append(QString("\n# Hole ")+QString::number(k+1)+QString("#\n"));
        meshControlData.append("\n#---------+-------+-------+--------#\n");
        meshControlData.append("# segment |  1st  |  2nd  | marker #\n");
        meshControlData.append("#---------+-------+-------+--------#\n");
        for (unsigned int j = 0; j < hole[k].size()-1; j++)
        {
            meshControlData.append(QString::number(segmentsIndex)+QString(":   "));
            meshControlData.append(QString::number(segmentsIndex)+QString("    "));
            meshControlData.append(QString::number(segmentsIndex+1)+QString("    "));
            meshControlData.append(QString::number(hole[k][j][2])+QString("\n"));
            segmentsIndex += 1;
        }
        meshControlData.append(QString::number(segmentsIndex)+QString(":   "));
        meshControlData.append(QString::number(segmentsIndex)+QString("    "));
        meshControlData.append(QString::number(segmentsIndex+1-hole[k].size())+QString("    "));
        meshControlData.append(QString::number(hole[k][hole[k].size()-1][2])+QString("\n"));
        segmentsIndex += 1;
        k++;
    }
    QByteArray meshControlDataByte = meshControlData.toUtf8();
    QDir *folder = new QDir;
    bool exist = folder->exists(QDir::currentPath()+QString("/Mesh"));
    if (!exist)
    {
        bool ok = folder->mkdir(QDir::currentPath()+QString("/Mesh"));
        if(!ok)
        {
            QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹创建失败！"));
            error = 1;
        }
    }

    QFile meshControlDataFile(QDir::currentPath()+QString("/Mesh/PartMesh")
                              +QString::number(partIndex+1)+QString(".d"));
    if (meshControlDataFile.exists())
    {
        QFile::remove(QDir::currentPath()+QString("/Mesh")
                      +QString::number(partIndex+1)+QString(".d"));
    }

    if (!meshControlDataFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("创建文件"),tr("文件创建失败！"));
        error = 2;
    }
    meshControlDataFile.write(meshControlDataByte,meshControlDataByte.length());
    meshControlDataFile.close();

    return error;
}

std::vector<std::vector<double> > PartWindow::createBoundaryNodes()
{
    int boundaryIndex = model->getPart(partIndex)->BCPI;
    std::vector<std::vector<double>> boundaryNodes;
    boundaryNodes = createNodes(unsigned(boundaryIndex),2);
    return boundaryNodes;
}

std::vector<std::vector<std::vector<double> > > PartWindow::createHoleNodes()
{
    std::vector<int> HCPI = model->getPart(partIndex)->HCPI;
    std::vector<std::vector<std::vector<double>>> holeNodes;
    holeNodes.resize(HCPI.size());
    for (unsigned int i = 0; i < HCPI.size(); i++)
        holeNodes[i] = createNodes(unsigned(HCPI[i]),1);
    return holeNodes;
}

std::vector<std::vector<double> > PartWindow::createNodes(unsigned int index, int direction)
{
    std::vector<std::vector<double>> NODES;
    std::vector<std::vector<std::vector<int>>> NewCPI;
    if (direction == 1)
        NewCPI = CPI;
    else
        NewCPI = RCPI;
    if (PR[unsigned(NewCPI[index][0][0])].getClosed())
    {
        if (PR[unsigned(NewCPI[index][0][0])].getType() == 3)
        {
            const int nodes = 100;
            NODES.resize(nodes);
            QPointF C = PR[unsigned(NewCPI[index][0][0])].getCenterOfCircle();
            double R = PR[unsigned(NewCPI[index][0][0])].getRadius();
            for (unsigned int i = 0; i < nodes; i++)
            {
                NODES[i].resize(3);
                NODES[i][2] = NewCPI[index][0][0] + 1;
                if (direction == 1)
                {
                    NODES[i][0] = C.x() + R * qCos(-2*Pi*i/nodes);
                    NODES[i][1] = C.y() + R * qSin(-2*Pi*i/nodes);
                }
                else if (direction == 2)
                {
                    NODES[i][0] = C.x() + R * qCos(2*Pi*i/nodes);
                    NODES[i][1] = C.y() + R * qSin(2*Pi*i/nodes);
                }
            }
        }
        return NODES;
    }
    NODES.resize(1);
    NODES[0].resize(3);
    NODES[0][2] = NewCPI[index][0][0] + 1;
    if (NewCPI[index][1][0] == 1)
    {
        NODES[0][0] = PR[unsigned(NewCPI[index][0][0])].getEndPoint().x();
        NODES[0][1] = PR[unsigned(NewCPI[index][0][0])].getEndPoint().y();
    }
    else
    {
        NODES[0][0] = PR[unsigned(NewCPI[index][0][0])].getBeginPoint().x();
        NODES[0][1] = PR[unsigned(NewCPI[index][0][0])].getBeginPoint().y();
    }
    for (unsigned int i = 1; i < NewCPI[index][0].size(); i++)
    {
        if (PR[unsigned(NewCPI[index][0][i])].getType() == 1)
        {
            NODES.resize(NODES.size()+1);
            NODES[NODES.size()-1].resize(3);
            NODES[NODES.size()-1][2] = NewCPI[index][0][i] + 1;
            if (NewCPI[index][1][i] == 1)
            {
                NODES[NODES.size()-1][0] = PR[unsigned(NewCPI[index][0][i])].getEndPoint().x();
                NODES[NODES.size()-1][1] = PR[unsigned(NewCPI[index][0][i])].getEndPoint().y();
            }
            else
            {
                NODES[NODES.size()-1][0] = PR[unsigned(NewCPI[index][0][i])].getBeginPoint().x();
                NODES[NODES.size()-1][1] = PR[unsigned(NewCPI[index][0][i])].getBeginPoint().y();
            }
        }
    }
    return NODES;
}

double PartWindow::length(int index)
{
    double length = 0;
    for (unsigned int i = 0; i < CPI[unsigned(index)][0].size(); i++)
    {
        if (PR[unsigned(CPI[unsigned(index)][0][i])].getType() == 3)
        {
            double R = PR[unsigned(CPI[unsigned(index)][0][i])].getRadius();
            length += 2 * Pi * R;
        }
        else if (PR[unsigned(CPI[unsigned(index)][0][i])].getType() == 1)
        {
            QPointF BP = PR[unsigned(CPI[unsigned(index)][0][i])].getBeginPoint();
            QPointF EP = PR[unsigned(CPI[unsigned(index)][0][i])].getEndPoint();
            double distance = sqrt(qPow(BP.x()-EP.x(),2) + qPow(BP.y()-EP.y(),2));
            length += distance;
        }
    }

    return length;
}

bool PartWindow::saveMeshData()
{
    QString NodesFilePath = QString("Mesh/PartMesh")
            + QString::number(partIndex+1) + QString(".n");
    QString ElementsFilePath = QString("Mesh/PartMesh")
            + QString::number(partIndex+1) + QString(".e");
    QString SidesFilePath = QString("Mesh/PartMesh")
            + QString::number(partIndex+1) + QString(".s");

    QFile NodesFile(NodesFilePath);
    QFile ElementsFile(ElementsFilePath);
    QFile SidesFile(SidesFilePath);

    if (!NodesFile.exists()||!ElementsFile.exists()||!SidesFile.exists())
    {
        QMessageBox::warning(this,"错误","结点信息文件被删除");
        return false;
    }

    if (!NodesFile.open(QIODevice::ReadOnly|QIODevice::Text) ||
        !ElementsFile.open(QIODevice::ReadOnly|QIODevice::Text) ||
        !SidesFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","单元文件被删除");
        return false;
    }

    QTextStream NodesStream(&NodesFile);
    QTextStream ElementsStream(&ElementsFile);
    QTextStream SidesStream(&SidesFile);

    QStringList tempList;

    int NodeNumber = NodesStream.readLine().toInt();
    int ELementNumber = ElementsStream.readLine().toInt();
    int SideNumber = SidesStream.readLine().toInt();

    MatrixXd Nodes;
    Nodes.resize(NodeNumber,2);

    MatrixXi Elements;
    Elements.resize(ELementNumber,6);

    MatrixXd ElementsCircumcenter;
    ElementsCircumcenter.resize(ELementNumber,2);

    MatrixXi Sides;
    Sides.resize(SideNumber,2);

    for (int i = 0; i < NodeNumber; i++)
    {
        tempList = NodesStream.readLine().simplified().split(" ");
        Nodes(i,0) = tempList.at(1).toDouble();
        Nodes(i,1) = tempList.at(2).toDouble();
    }
    for (int i = 0; i < ELementNumber; i++)
    {
        tempList = ElementsStream.readLine().simplified().split(" ");
        Elements(i,0) = tempList.at(1).toInt();
        Elements(i,1) = tempList.at(2).toInt();
        Elements(i,2) = tempList.at(3).toInt();
        Elements(i,3) = tempList.at(7).toInt();
        Elements(i,4) = tempList.at(8).toInt();
        Elements(i,5) = tempList.at(9).toInt();
        ElementsCircumcenter(i,0) = tempList.at(10).toDouble();
        ElementsCircumcenter(i,1) = tempList.at(11).toDouble();
    }
    for (int i = 0; i < SideNumber; i++)
    {
        tempList = SidesStream.readLine().simplified().split(" ");
        Sides(i,0) = tempList.at(1).toInt();
        Sides(i,1) = tempList.at(2).toInt();
    }
    Part *part = model->getPart(partIndex);

    part->NN = NodeNumber;
    part->NE = ELementNumber;
    part->NS = SideNumber;
    part->CXY = Nodes;
    part->EN = Elements;
    part->EC = ElementsCircumcenter;
    part->SI = Sides;

    return true;
}

void PartWindow::drawMesh()
{
    on_actionSubmittedModel_triggered();
    int ElementNumber = model->getPart(partIndex)->NE;
    MSN = ElementNumber;
    MatrixXd Nodes = model->getPart(partIndex)->CXY;
    MatrixXi Elements = model->getPart(partIndex)->EN;
    MS = new QLineSeries*[ElementNumber];
    for (int i = 0; i < ElementNumber; i++)
    {
        QPen pen;
        pen.setWidth(2);
        MS[i] = new QLineSeries();
        for (int j = 0; j < 3; j++)
            MS[i]->append(Nodes(Elements(i,j),0),Nodes(Elements(i,j),1));
        MS[i]->append(Nodes(Elements(i,0),0),Nodes(Elements(i,0),1));
        ui->chartView->chart()->addSeries(MS[i]);
    }
    std::vector<double> range = DXF->getRange();
    QChart *chart = ui->chartView->chart();

    chart->createDefaultAxes();
    auto axisx = chart->axes(Qt::Horizontal);
    auto axisy = chart->axes(Qt::Vertical);
    QAbstractAxis *axisX = axisx.at(0);
    QAbstractAxis *axisY = axisy.at(0);
    axisX->setRange(range[0],range[1]);
    axisY->setRange(range[2],range[3]);
    chart->legend()->setVisible(false);
}

void PartWindow::on_mouseMovePoint(QPoint point)
{
    QPointF pt = ui->chartView->chart()->mapToValue(point);
    labXYVaulue->setText(QString::asprintf("坐标：X=%.1f,Y=%.2f",pt.x(),pt.y()));
}

void PartWindow::on_actionZoomIn_triggered()
{
    ui->chartView->chart()->zoom(1.2);
    ui->chartView->setZoomFactor(ui->chartView->getZoomFactor()*1.2);
}

void PartWindow::on_actionZoomOut_triggered()
{
    ui->chartView->chart()->zoom(0.8);
    ui->chartView->setZoomFactor(ui->chartView->getZoomFactor()*0.8);
}

void PartWindow::on_actionZoomReset_triggered()
{
    ui->chartView->chart()->zoomReset();
    ui->chartView->setZoomFactor(1);
}

void PartWindow::on_actionBoundary_triggered()
{
    ui->actionHoleNew->setChecked(false);
    ui->chartView->setChooseMode(1);
}

void PartWindow::on_actionHoleNew_triggered()
{
    ui->actionBoundary->setChecked(false);
    ui->chartView->setChooseMode(1);
}

void PartWindow::on_actionCancelSelect_triggered()
{
    if (ui->actionCancelSelect->isChecked())
        ui->chartView->setChooseMode(2);
    else
        ui->chartView->setChooseMode(1);
}

void PartWindow::on_actionReSelect_triggered()
{
    ui->chartView->iniLineSeriesColor();
}

void PartWindow::on_actionOK_triggered()
{
    std::vector<int> CP = ui->chartView->getChosenPrimitive();
    //失败处理
    if (CP.size() == 0)
    {
        QString dlgTitle = "错误";
        QString strInfo = "请选择闭合区域";
        QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    else if (CP.size() > 1 && ui->actionBoundary->isChecked())
    {
        QString dlgTitle = "错误";
        QString strInfo = "仅能选择一个闭合区域作为边界";
        QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    //导入边界
    QString dlgTitle = "成功";
    QString strInfo = "导入成功";
    Part *part = model->getPart(partIndex);

    if (ui->actionBoundary->isChecked())    //导入边界
        part->BCPI = CP[0];
    else if (ui->actionHoleNew->isChecked())    //导入孔洞
    {
        //导入失败处理
        //边界未定义错误
        QString dlgTitleError = "导入失败";
        if (part->BCPI == -1)
        {
            QMessageBox::information(this,dlgTitleError,"请先定义边界",
                                     QMessageBox::Ok,QMessageBox::NoButton);
            return;
        }

        part->HCPI = CP;
    }
    QMessageBox::information(this,dlgTitle,strInfo,
                             QMessageBox::Ok,QMessageBox::NoButton);
}

void PartWindow::on_actionSubmittedModel_triggered()
{
    Part *part = model->getPart(partIndex);
    std::vector<int> index;
    std::vector<QColor> color;
    index.push_back(part->BCPI);
    color.push_back(Qt::yellow);
    for (int i = 0; i < int(part->HCPI.size()); i++)
    {
        index.push_back(part->HCPI[unsigned(i)]);
        color.push_back(Qt::green);
    }
    ui->chartView->setLineSeriesColor(index,color);
}

void PartWindow::on_actionModelControlData_triggered()
{
    MeshParameter *meshParameter = new MeshParameter(this);
    meshParameter->show();
    int ret = meshParameter->exec();
    if (ret == QDialog::Rejected)
        return;
    double boundaryNodes = meshParameter->getBoundaryNodes();
    double holeNodes = meshParameter->getHoleNodes();

    int error = createMeshControlData(boundaryNodes,holeNodes);
    if (error)
    {
        QMessageBox::warning(this,"错误","网格参数文件生成失败");
        return;
    }

    ModelData *modeldata = new ModelData(this, partIndex);
    modeldata->show();
}

void PartWindow::on_actionMesh_triggered()
{
    QString filePath = QString("Mesh/PartMesh")+QString::number(partIndex+1)+QString(".d");
    QFile aFile(filePath);
    if (!aFile.exists())
    {
        QMessageBox::warning(this,"错误","请先生产模型数据");
        return;
    }
    QByteArray filePathByteArray = filePath.toLatin1();
    argc = 2;
    argv[1] = filePathByteArray.data();

    EasyMesh em;
    em.algor(argc, argv);

    bool saveState = saveMeshData();
    if (saveState == false)
    {
        QMessageBox::information(this,tr("划分网格"),tr("数据保存失败"));
        return;
    }
    drawMesh();
    QMessageBox::information(this,tr("划分网格"),tr("网格划分成功！"));
}

void PartWindow::on_actionClearMesh_triggered()
{
    for (int i = 0; i < MSN; i++)
        ui->chartView->chart()->removeSeries(MS[i]);
}

