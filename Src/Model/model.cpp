#include "model.h"
#include "LU.h"
#include "bc.h"
#include "load.h"
#include <QDir>
#include <QMessageBox>
#include <iostream>

const double pi = 3.14159265358979323846264338328;

Model::Model()
{
    std::vector<Material> material;
    std::vector<Part> part;
    this->material = material;
    this->part = part;
}

Model::~Model()
{

}

void Model::setElementNode(MatrixXi EN)
{
    this->EN = EN;
    this->NE = int(EN.rows());
}

void Model::setElementNumber(int NE)
{
    this->NE = NE;
}

MatrixXi Model::getElementNode()
{
    return this->EN;
}

int Model::getElementNumber()
{
    return this->NE;
}

void Model::setNodeCoordinate(MatrixXd CXY)
{
    this->CXY = CXY;
    this->NN = int(CXY.rows());
}

void Model::setNodeNumber(int NN)
{
    this->NN = NN;
}

MatrixXd Model::getNodeCoordinate()
{
    return this->CXY;
}

int Model::getNodeNumber()
{
    return this->NN;
}

void Model::setSide(MatrixXi SI)
{
    this->SI = SI;
}

void Model::setSideNumber(int NS)
{
    this->NS = NS;
}

MatrixXi Model::getSide()
{
    return SI;
}

int Model::getSideNumber()
{
    return NS;
}

void Model::setFixedDegree(VectorXi IFIX)
{
    this->IFIX = IFIX;
}

VectorXi Model::getFixedDegree()
{
    return this->IFIX;
}

void Model::setLoad(VectorXd F)
{
    this->F = F;
}

VectorXd Model::getLoad()
{
    return this->F;
}

void Model::addMaterial(Material M)
{
    this->material.push_back(M);
}

void Model::removeMaterial(int index)
{
    material.erase(material.begin()+index);
}

Material *Model::getMaterial(int index)
{
    return &this->material[unsigned(index)];
}

int Model::getMaterialNumber()
{
    return int(material.size());
}

void Model::addPart(Part P)
{
    this->part.push_back(P);
}

void Model::removePart(int index)
{
    part.erase(part.begin()+index);
}

Part *Model::getPart(int index)
{
    return &this->part[unsigned(index)];
}

void Model::setPart(int index,Part P)
{
    part[unsigned(index)] = P;
}

int Model::getPartNumber()
{
    return int(part.size());
}

int Model::getBoundaryConditionNumber()
{
    return NBC;
}

void Model::addBoundaryConditionNumber(int N)
{
    NBC += N;
}

int Model::getLoadNumber()
{
    return NL;
}

void Model::addLoadNumber(int N)
{
    NL += N;
}

void Model::setJobArgument(int PT,int ET, double T, int SM, int SLE, int PI, int MI)
{
    this->PT = PT;
    this->ET = ET;
    this->T = T;
    this->SM = SM;
    this->SLE = SLE;
    this->PI = PI;
    this->MI = MI;
    this->NE = part[unsigned(PI)].NE;
    this->NN = part[unsigned(PI)].NN;
    this->NS = part[unsigned(PI)].NS;
    this->EN = part[unsigned(PI)].EN;
    this->CXY = part[unsigned(PI)].CXY;
    this->SI = part[unsigned(PI)].SI;
}

void Model::getJobArgument(int &PT,int &ET, double &T, int &SM, int &SLE, int &PI, int &MI)
{
    PT = this->PT;
    ET = this->ET;
    T = this->T;
    SM = this->SM;
    SLE = this->SLE;
    PI = this->PI;
    MI = this->MI;
}

int Model::getElementType()
{
    return ET;
}

void Model::TrigularElement3To6()
{
    int NS = part[unsigned(PI)].NS;
    MatrixXd tCXY = CXY;
    CXY.resize(NN+NS,2);
    CXY.block(0,0,NN,2) = tCXY;

    int *SideChosenNode = new int[NS]();
    int NodeIndex = 0;
    int SideIndex,iNode,jNode;
    double ix,iy,jx,jy;

    MatrixXi NewSI;
    NewSI.resize(SI.rows(),3);
    NewSI.block(0,0,SI.rows(),2) = SI;

    for (int i = 0; i < NE; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            SideIndex = EN(i,j+3);
            if (SideChosenNode[SideIndex] > 0)
            {
                EN(i,j+3) = SideChosenNode[SideIndex];
                continue;
            }
            iNode = EN(i,j);
            jNode = EN(i,(j+1)%3);
            ix = CXY(iNode,0);
            iy = CXY(iNode,1);
            jx = CXY(jNode,0);
            jy = CXY(jNode,1);
            EN(i,j+3) = NN + NodeIndex;
            CXY(NN+NodeIndex,0) = (ix + jx) / 2;
            CXY(NN+NodeIndex,1) = (iy + jy) / 2;
            NewSI(SideIndex,2) = NN + NodeIndex;
            SideChosenNode[SideIndex] = NN + NodeIndex;
            NodeIndex++;
        }
    }
    SI = NewSI;
    NN += NS;
}

MatrixXi Model::calcID
(int NDF, int NN, VectorXi IFIX)
{
    //NDF:节点自由度
    //NN:节点数
    //IFIX:约束自由度

    //声明节点位移信息矩阵
    MatrixXi ID;
    ID.resize(NN,NDF);

    int GKA;  //总刚地址

    for (int i = 0; i < NN; i++)
    {
        for (int j = 0; j < NDF; j++)
        {
            ID(i,j) = 0;
            GKA = NDF * i + j;
            if (IFIX[unsigned(GKA)] == 1)
                ID(i,j) = 1;
        }
    }
    int DEGREE = 0;
    for (int i = 0; i < NN; i++)
    {
        for (int j = 0; j < NDF; j++)
        {
            if (ID(i,j) == 1)
                ID(i,j) = 0;
            else
            {
                DEGREE = DEGREE + 1;
                ID(i,j) = DEGREE;
            }
        }
    }

    return ID;
}

MatrixXi Model::getID()
{
    return this->ID;
}

MatrixXi Model::calcLM
(int NDF, int NNE, int NE,int NN,VectorXi IFIX, MatrixXi EN)
{
    //NDF:节点自由度
    //NNE:单元结点数
    //NE:单元数
    //NN:节点数
    //EN:单元结点编号

    MatrixXi LM;
    LM.resize(NE,NDF*NNE);

    MatrixXi ID = calcID(NDF,NN,IFIX);
    for (int i = 0; i < NE; i++)
        for (int j = 0; j < NNE; j++)
            for (int k = 0; k < NDF; k++)
                LM(i,NDF * j + k) = ID(EN(i,j),k);

    return LM;
}

MatrixXi Model::getLM()
{
    return this->LM;
}

VectorXi Model::calcM
(int NDF, int NNE, int NE,int NN,VectorXi IFIX, MatrixXi EN)
{
    //NDF:节点自由度
    //NNE:单元结点数
    //NE:单元数
    //NN:节点数
    //EN:单元结点编号

    int NFIX = IFIX.sum();  //约束自由度数
    int ND = NN * NDF;  //总自由度

    int NonzeroRow;
    int min_element;

    VectorXi M;
    M.resize(ND-NFIX);

    MatrixXi LM = calcLM(NDF,NNE,NE,NN,IFIX,EN);

    for (int i = 0; i < ND - NFIX; i++)
    {
        NonzeroRow = i + 1;
        for (int j = 0; j< NE; j++)
        {
            int sign = 0;
            min_element = INT_MAX;
            for (int k = 0; k < NDF * NNE; k++)
            {
                if (LM(j,k) < min_element && LM(j,k) != 0)
                    min_element = LM(j,k);
                if (i + 1 == LM(j,k))
                    sign = 1;
            }
            if (sign == 1 && min_element < NonzeroRow)
                NonzeroRow = min_element;
        }
        M[i] = NonzeroRow;
    }

    return M;
}

VectorXi Model::getM()
{
    return this->M;
}

VectorXi Model::calcAM
(int NDF, int NNE, int NE,int NN,VectorXi IFIX, MatrixXi EN)
{
    //NDF:节点自由度
    //NNE:单元结点数
    //NE:单元数
    //NN:节点数
    //EN:单元结点编号

    int NFIX = IFIX.sum();  //约束自由度数
    int ND = NN * NDF;  //总自由度

    VectorXi AM,Height;
    AM.resize(ND - NFIX + 1);
    Height.resize(ND - NFIX);

    VectorXi M = calcM(NDF,NNE,NE,NN,IFIX,EN);

    for (int i = 0;i < ND - NFIX; i++)
    {
        AM[i] = 1;
        Height[i] = i - M[i] + 2;
        for (int j = 0; j < i; j++)
            AM[i] = AM[i] + Height[j];
    }
    AM[ND - NFIX] = AM[ND - NFIX - 1] + Height[ND - NFIX - 1];

    return AM;
}

VectorXi Model::getAM()
{
    return this->AM;
}

MatrixXd Model::calcGK(int ET,int SM,int MI,double T)
{
    int NDF = 2,NNE = 3;
    MatrixXd coords;
    if (ET == 3)   {coords.resize(3,2);NDF = 2;NNE = 3;}
    else if (ET == 6) {coords.resize(6,2);NDF = 2; NNE = 6;}
    this->ID = calcID(NDF,NN,IFIX);
    this->LM = calcLM(NDF,NNE,NE,NN,IFIX,EN);
    this->AM = calcAM(NDF,NNE,NE,NN,IFIX,EN);
    this->M = calcM(NDF,NNE,NE,NN,IFIX,EN);

    MatrixXd GK;
    //开总刚矩阵维数
    switch(SM)
    {
    case 0:
        GK.resize(2*NN-IFIX.sum(),2*NN-IFIX.sum());
        break;
    case 1:
        GK.resize(AM.tail(1)(0)-1,1);
        break;
    case 2:
    {
        int cols = 0;
        for (int i = 0; i < NE; i++)
        {
            if (LM.row(i).maxCoeff() - LM.row(i).minCoeff() > cols && LM.row(i).minCoeff() > 0)
                cols = LM.row(i).maxCoeff() - LM.row(i).minCoeff() + 1;
            else if (LM.row(i).maxCoeff() - LM.row(i).minCoeff() > cols && LM.row(i).minCoeff() == 0)
            {
                int RowMin = LM.row(i).maxCoeff();
                for (int j = 0; j < 6; j++)
                    if (LM(i,j) >0 && LM(i,j) < RowMin)
                        RowMin = LM(i,j);
                cols = LM.row(i).maxCoeff() -RowMin + 1;
            }
        }
        GK.resize(2*NN-IFIX.sum(),cols);
        break;
    }
    }
    GK.setZero();
    Material material = this->material[unsigned(MI)];

    for (int i = 0; i < NE; i++)
    {
        //单元刚度矩阵
        MatrixXd EK;
        for (int j = 0; j < NNE; j++)
            for (int k = 0; k < NDF; k++)
                coords(j,k) = CXY(EN(i,j),k);
        if (ET == 3) {
            TriangularElementThreeNode element;
            coords.resize(3,2);
            EK = element.calcEK(coords,material,T);
        }
        else {
            TriangularElementSixNode element;
            EK = element.calcEK(coords,material,T);
        }
        //组装总刚矩阵
        int row,column;
        for (int j = 0; j < NDF * NNE; j++)
        {
            row = ID(EN(i,j/NDF),j % NDF) - 1;
            if (row < 0)
                continue;
            for (int k = 0; k < NDF * NNE; k++)
            {
                column = ID(EN(i,k/NDF),k % NDF) - 1;
                if (column < 0)
                    continue;
                if (row > column)
                    continue;
                switch (SM)
                {
                case 0:
                    GK(row,column) += EK(j,k); break;
                case 1:
                {
                    int rowIndex = AM(column) + column - row - 1;
                    GK(rowIndex) += EK(j,k); break;
                }
                case 2:
                    GK(row,column - row) += EK(j,k); break;
                }
            }  //k loop
        }  //j loop
    }  // i loop
    this->GK = GK;
    return GK;
}

void Model::calcBoundaryCondition()
{
    int NDF = 2;
    if (ET == 3) NDF = 2;
    else if (ET == 6) NDF = 2;
    IFIX.resize(NDF*NN);
    IFIX.setZero();

    std::vector<Primitive> PR = part[unsigned(PI)].DXF->getPrimitives();
    std::vector<BC> BC = part[unsigned(PI)].BC;
    for (unsigned int i = 0; i < BC.size(); i++)
    {
        Primitive primitive = PR[unsigned(BC[i].PRIndex)];
        QPointF BeginPoint = primitive.getBeginPoint();
        QPointF EndPoint = primitive.getEndPoint();
        QPointF BP = BeginPoint,EP = EndPoint;

        if (!(BeginPoint.x() - EndPoint.x() < -0.000001 ||
                (qAbs(BeginPoint.x() - EndPoint.x()) <= 0.000001 &&
                      BeginPoint.y() - EndPoint.y() < -0.000001)))
        {
            BP = EndPoint;
            EP = BeginPoint;
        }
        if (qAbs(BC[i].MinRange - BC[i].MaxRange) < 0.000001)//点边界
        {
            double distance = INT_MAX, D;
            unsigned int DI = 0;
            QPointF P;
            if (PR[unsigned(BC[i].PRIndex)].getType() == 1)  //直线边界
            {
                P.setX(BP.x() + (EP.x()-BP.x())*BC[i].MinRange);
                P.setY(BP.y() + (EP.y()-BP.y())*BC[i].MinRange);
            }
            else if (PR[unsigned(BC[i].PRIndex)].getType() == 3)  //圆形边界
            {

                QPointF CC = PR[unsigned(BC[i].PRIndex)].getCenterOfCircle();
                double R = PR[unsigned(BC[i].PRIndex)].getRadius();
                P.setX(CC.x()+R*qCos(2*pi*BC[i].MinRange));
                P.setY(CC.y()+R*qSin(2*pi*BC[i].MinRange));
            }
            for (unsigned int j = 0; j < unsigned(NN); j++)
            {
                D = sqrt(qPow(P.x()-CXY(j,0),2)+qPow(P.y()-CXY(j,1),2));
                if (D < distance)
                {
                    distance = D;
                    DI = j;
                }
            }

            if (BC[i].DegreeConstraintX)
                IFIX(2*DI) = 1;
            if (BC[i].DegreeConstraintY)
                IFIX(2*DI+1) = 1;
            continue;
        }
        double A = EP.y() - BP.y();
        double B = BP.x() - EP.x();
        double C = -BP.x() * A - EP.y() * B;
        double length = sqrt(qPow(BP.x()-EP.x(),2)+qPow(BP.y()-EP.y(),2));
        double x,y,s,distance,p;
        if (PR[unsigned(int(BC[i].PRIndex))].getType() == 1)  //直线边界
        {
            for (unsigned int j = 0; j < unsigned(NN); j++)
            {
                x = CXY(j,0);
                y = CXY(j,1);
                distance = qAbs(A*x+B*y+C)/sqrt(qPow(A,2)+qPow(B,2));
                s = sqrt(qPow(x-BP.x(),2)+qPow(y-BP.y(),2));
                p = sqrt(qPow(s,2)-qPow(distance,2))/length;
                if (p >= BC[i].MinRange && p <= BC[i].MaxRange && distance < 0.001)
                {
                    if (BC[i].DegreeConstraintX)
                        IFIX(2*j) = 1;
                    if (BC[i].DegreeConstraintY)
                        IFIX(2*j+1) = 1;
                }
            }
        }
        else if (PR[unsigned(BC[i].PRIndex)].getType() == 3)  //圆边界
        {
            QPointF CC = PR[unsigned(BC[i].PRIndex)].getCenterOfCircle();
            double R = PR[unsigned(BC[i].PRIndex)].getRadius();
            for (unsigned int j = 0; j < unsigned(NN); j++)
            {
                x = CXY(j,0);
                y = CXY(j,1);
                distance = sqrt(qPow(x-CC.x(),2)+qPow(y-CC.y(),2));
                if (qAbs(distance-R) > 0.001)
                    continue;
                double deltaX = x-CC.x();
                double deltaY = y-CC.y();
                double theta;
                if (qAbs(deltaX) < 0.001 && deltaY > 0)
                    theta = pi/2;
                else if (qAbs(deltaX) < 0.001 && deltaY < 0)
                    theta = 3*pi/2;
                else
                {
                    theta = atan(deltaY/deltaX);
                    if (deltaX < 0)
                        theta += pi;
                    else if (deltaX > 0 && deltaY < 0)
                        theta += 2*pi;
                }

                if (theta/(2*pi) >= BC[i].MinRange && theta/(2*pi) <= BC[i].MaxRange)
                {
                    if (BC[i].DegreeConstraintX)
                        IFIX(2*j) = 1;
                    if (BC[i].DegreeConstraintY)
                        IFIX(2*j+1) = 1;
                }
            }
        }
    }
}

void Model::calcLoad()
{
    int NDF = 2;
    if (ET == 3) NDF = 2;
    else if (ET == 6) NDF = 2;
    VectorXd Load;
    Load.resize(NDF*NN);
    Load.setZero();

    std::vector<Primitive> PR = part[unsigned(PI)].DXF->getPrimitives();
    std::vector<LOAD> F = part[unsigned(PI)].F;

    double Density = material[unsigned(MI)].Density;

    for (unsigned int i = 0; i < F.size(); i++)
    {
        if (F[i].LoadType == 1)  //自重荷载
        {
            calcGravityLoad(this->ET,CXY,EN,Density,F[i].BPX,F[i].BPY,this->T,Load);
            continue;
        }

        Primitive primitive = PR[unsigned(F[i].PRIndex)];
        QPointF BeginPoint = primitive.getBeginPoint();
        QPointF EndPoint = primitive.getEndPoint();
        QPointF BP = BeginPoint,EP = EndPoint;

        //计算起点、终点坐标
        if (!(BeginPoint.x() - EndPoint.x() < -0.000001 ||
                (qAbs(BeginPoint.x() - EndPoint.x()) <= 0.000001 &&
                      BeginPoint.y() - EndPoint.y() < -0.000001)))
        {
            BP = EndPoint;
            EP = BeginPoint;
        }

        if (qAbs(F[i].MinRange - F[i].MaxRange) < 0.001)  //点边界
        {
            double distance = INT_MAX, D;
            unsigned int DI = 0;
            QPointF P;
            if (PR[unsigned(F[i].PRIndex)].getType() == 1)  //直线上的点
            {
                P.setX(BP.x() + (EP.x()-BP.x())*F[i].MinRange);
                P.setY(BP.y() + (EP.y()-BP.y())*F[i].MinRange);
            }
            else if (PR[unsigned(F[i].PRIndex)].getType() == 3)  //圆形上的点
            {

                QPointF CC = PR[unsigned(F[i].PRIndex)].getCenterOfCircle();
                double R = PR[unsigned(F[i].PRIndex)].getRadius();
                P.setX(CC.x()+R*qCos(2*pi*F[i].MinRange));
                P.setY(CC.y()+R*qSin(2*pi*F[i].MinRange));
            }
            for (unsigned int j = 0; j < unsigned(NN); j++)
            {
                D = sqrt(qPow(P.x()-CXY(j,0),2)+qPow(P.y()-CXY(j,1),2));
                if (D < distance)
                {
                    distance = D;
                    DI = j;
                }
            }
            Load(2*DI) += (F[i].BPX + F[i].EPX);
            Load(2*DI+1) += (F[i].BPY + F[i].EPY);
            continue;
        }

        double A = EP.y() - BP.y();
        double B = BP.x() - EP.x();
        double C = -BP.x() * A - EP.y() * B;
        double length = sqrt(qPow(BP.x()-EP.x(),2)+qPow(BP.y()-EP.y(),2));
        double x1,y1,x2,y2,s1,s2,distance1,distance2,p1,p2,BPX,BPY,EPX,EPY;

        if (PR[unsigned(F[i].PRIndex)].getType() == 1)  //直线边界
        {
            for (unsigned int j = 0; j < unsigned(NS); j++)
            {
                x1 = CXY(SI(j,0),0);
                y1 = CXY(SI(j,0),1);
                x2 = CXY(SI(j,1),0);
                y2 = CXY(SI(j,1),1);
                distance1 = qAbs(A*x1+B*y1+C)/sqrt(qPow(A,2)+qPow(B,2));
                distance2 = qAbs(A*x2+B*y2+C)/sqrt(qPow(A,2)+qPow(B,2));
                if (distance1 > 0.001 || distance2 > 0.001)
                    continue;
                s1 = sqrt(qPow(x1-BP.x(),2)+qPow(y1-BP.y(),2));
                s2 = sqrt(qPow(x2-BP.x(),2)+qPow(y2-BP.y(),2));
                p1 = sqrt(qPow(s1,2)-qPow(distance1,2))/length;
                p2 = sqrt(qPow(s2,2)-qPow(distance2,2))/length;
                if (p1 >= F[i].MinRange && p1 <= F[i].MaxRange &&
                        p2 >= F[i].MinRange && p2 <= F[i].MaxRange)
                {
                    if (F[i].LoadType == 2)  //均布荷载
                    {
                        BPX = F[i].BPX;
                        BPY = F[i].BPY;
                        EPX = BPX;
                        EPY = BPY;
                    }
                    else  //线性分布荷载
                    {
                        BPX = F[i].BPX + (F[i].EPX-F[i].BPX) * p1;
                        BPY = F[i].BPY + (F[i].EPY-F[i].BPY) * p1;
                        EPX = F[i].BPX + (F[i].EPX-F[i].BPX) * p2;
                        EPY = F[i].BPY + (F[i].EPY-F[i].BPY) * p2;
                    }
                    VectorXd DL;
                    DL.resize(4);
                    DL << BPX, BPY, EPX, EPY;
                    MatrixXi aSI = SI.row(j);
                    calcLinearDistributedLoad(ET,aSI,Load,DL,T);
                }
            }
        }
        else if (PR[unsigned(int(F[i].PRIndex))].getType() == 3)  //圆边界
        {
            QPointF CC = PR[unsigned(int(F[i].PRIndex))].getCenterOfCircle();
            double R = PR[unsigned(int(F[i].PRIndex))].getRadius();
            for (unsigned int j = 0; j < unsigned(NS); j++)
            {
                x1 = CXY(SI(j,0),0);
                y1 = CXY(SI(j,0),1);
                x2 = CXY(SI(j,1),0);
                y2 = CXY(SI(j,1),1);
                double deltaX1 = x1-CC.x();
                double deltaY1 = y1-CC.y();
                double deltaX2 = x2-CC.x();
                double deltaY2 = y2-CC.y();
                double theta1,theta2;
                if (qAbs(deltaX1) < 0.001 && deltaY1 > 0)
                    theta1 = pi/2;
                else if (qAbs(deltaX1) < 0.001 && deltaY1 < 0)
                    theta1 = 3*pi/2;
                else
                {
                    theta1 = atan(deltaY1/deltaX1);
                    if (deltaX1 < 0)
                        theta1 += pi;
                    else if (deltaX1 > 0 && deltaY1 < 0)
                        theta1 += 2*pi;
                }
                if (qAbs(deltaX2) < 0.001 && deltaY2 > 0)
                    theta2 = pi/2;
                else if (qAbs(deltaX2) < 0.001 && deltaY2 < 0)
                    theta2 = 3*pi/2;
                else
                {
                    theta2 = atan(deltaY2/deltaX2);
                    if (deltaX2 < 0)
                        theta2 += pi;
                    else if (deltaX2 > 0 && deltaY2 < 0)
                        theta2 += 2*pi;
                }
                distance1 = sqrt(qPow(x1-CC.x(),2)+qPow(y1-CC.y(),2));
                distance2 = sqrt(qPow(x2-CC.x(),2)+qPow(y2-CC.y(),2));
                if (qAbs(distance1-R) > 0.001 || qAbs(distance2-R) > 0.001)
                    continue;
                if (distance1 > 0.001 || distance2 > 0.001)
                    continue;
                p1 = theta1 / (2*pi);
                p2 = theta2 / (2*pi);
                if (theta1/(2*pi) >= F[i].MinRange && theta1/(2*pi) <= F[i].MaxRange)
                {
                    if (F[i].LoadType == 2)  //均布荷载
                    {
                        BPX = F[i].BPX;
                        BPY = F[i].BPY;
                        EPX = BPX;
                        EPY = BPY;
                    }
                    else  //线性分布荷载
                    {
                        BPX = F[i].BPX + (F[i].EPX-F[i].BPX) * p1;
                        BPY = F[i].BPY + (F[i].EPY-F[i].BPY) * p1;
                        EPX = F[i].BPX + (F[i].EPX-F[i].BPX) * p2;
                        EPY = F[i].BPY + (F[i].EPY-F[i].BPY) * p2;
                    }

                    VectorXd DL;
                    DL.resize(4);
                    DL << BPX, BPY, EPX, EPY;
                    MatrixXi aSI = SI.row(j);
                    calcLinearDistributedLoad(ET,aSI,Load,DL,T);
                }
            }
        }
    }
    this->F = Load;
}

void Model::calcGravityLoad(int ET, MatrixXd CXY, MatrixXi EN,double Density,double GX,double GY,double T, VectorXd &Load)
{
    int NE = int(EN.rows());
    for (int j = 0; j < NE; j++)
    {
        MatrixXd CI = CXY.block(EN(j,0),0,1,2);
        MatrixXd CJ = CXY.block(EN(j,1),0,1,2);
        MatrixXd CM = CXY.block(EN(j,2),0,1,2);
        double S = 0;
        S += (CJ(0)*CM(1)-CM(0)*CJ(1));
        S -= (CI(0)*CM(1)-CM(0)*CI(1));
        S += (CI(0)*CJ(1)-CJ(0)*CI(1));
        S /= 2;
        double FX = S * T *Density * GX;
        double FY = S * T * Density * GY;

        switch (ET) {
        case 3:
        {
            for (int k = 0; k < 3; k++)
            {
                Load(2*EN(j,k)) += FX/3;
                Load(2*EN(j,k)+1) += FY/3;
            }
            break;
        }
        case 6:
        {
            for (int k = 3; k < 6; k++)
            {
                Load(2*EN(j,k)) += FX/3;
                Load(2*EN(j,k)+1) += FY/3;
            }
            break;
        }
        }
    }
}

void Model::calcLinearDistributedLoad
(int ET, MatrixXi SI, VectorXd &Load, VectorXd DL,double T)
{
    //Vector : DL << qx1, qy1, qx2, qy2;
    double l = qSqrt(qPow(CXY(SI(0),0)-CXY(SI(1),0),2)+
                     qPow(CXY(SI(0),1)-CXY(SI(1),1),2));
    double FX1 = DL(0)* l * T / 2;
    double FX2 = DL(2)* l * T / 2;
    double FY1 = DL(1)* l * T / 2;
    double FY2 = DL(3)* l * T / 2;
    switch(ET)
    {
    case 3:
    {
        Load(2*SI(0))      += (FX1 * 2 + FX2) / 3;
        Load(2*SI(0) + 1)  += (FY1 * 2 + FY2) / 3;
        Load(2*SI(1))      += (FX1 + FX2 * 2) / 3;
        Load(2*SI(1) + 1)  += (FY1 + FY2 * 2) / 3;
        break;
    }
    case 6:
    {
        Load(2*SI(2))      += (FX1 + FX2) * 2 /3;
        Load(2*SI(2) + 1)  += (FY1 + FY2) * 2 /3;
        Load(2*SI(0))      +=  FX1 / 3;
        Load(2*SI(0) + 1)  +=  FY1 / 3;
        Load(2*SI(1))      +=  FX2 / 3;
        Load(2*SI(1) + 1)  +=  FY2 / 3;
        break;
    }
    }
}

void Model::calcStrainStress()
{
    Matrix<double,3,2> XY;

    int NN = this->NN;
    if (ET == 6)
         NN -= part[unsigned(PI)].NS;

    MatrixXd STRESS,STRAIN;
    STRESS.resize(NN,3);
    STRAIN.resize(NN,3);
    STRESS.setZero();
    STRAIN.setZero();

    Matrix<double,3,1> strain;
    Matrix<double,3,1> stress;

    double E = material[unsigned(MI)].E;
    double ANU = material[unsigned(MI)].ANU;
    if (PT == 1)  //平面应变
    {
        E = E / (1 - ANU * ANU);
        ANU = ANU / (1 - ANU);
    }
    //弹性矩阵
    Matrix<double,3,3> D;
    D << 1,   ANU, 0,
         ANU, 1,   0,
         0,   0,  (1-ANU)/2;
    D = D * E / (1-ANU*ANU);

    VectorXi N;
    N.resize(NN);
    N.setZero();

    for (int i = 0; i < NE; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
            for (unsigned int k = 0; k < 2; k++)
                XY(j,k) = CXY(EN(i,j),k);


        //位移列阵
        VectorXd delta;
        int NDF = 2, NNE = 3;
        if (ET == 6) {NNE = 6;}
        delta.resize(2*NNE);

        for (int j = 0; j < NNE; j++)
        {
            for (int k = 0; k < NDF; k++)
            {
                if (ID(EN(i,j),k) != 0)
                    delta(2*j+k) = Delta[ID(EN(i,j),k)-1];
                else
                    delta(2*j+k) = 0;
            }
        }

        MatrixXd B;
        if (ET == 3)
        {
            B = calcStrainMatrix(ET,XY);
            strain = B * delta;
            stress = D * B * delta;
            for (int j = 0; j < 3; j++)
            {
                N(EN(i,j)) += 1;
                for (int k = 0; k < 3; k++)
                {
                    STRAIN(EN(i,j),k) += strain[k];
                    STRESS(EN(i,j),k) += stress[k];
                }
            }
        }
        else if (ET == 6)
        {
            Matrix<int,3,3> L;
            L << 1,0,0,
                 0,1,0,
                 0,0,1;

            for (int j = 0; j < 3; j++)
            {
                B = calcStrainMatrix(ET,XY,L(j,0),L(j,1),L(j,2));
                strain = B * delta;
                stress = D * B *delta;
                N(EN(i,j)) += 1;
                for (int k = 0; k < 3; k++)
                {
                    STRAIN(EN(i,j),k) += strain[k];
                    STRESS(EN(i,j),k) += stress[k];
                }
            }
        }

    }

    for (int i = 0; i < NN; i++)
    {
        STRAIN(i,0) /= N(i);
        STRAIN(i,1) /= N(i);
        STRAIN(i,2) /= N(i);
        STRESS(i,0) /= N(i);
        STRESS(i,1) /= N(i);
        STRESS(i,2) /= N(i);
    }
    this->STRAIN = STRAIN;
    this->STRESS = STRESS;
}

MatrixXd Model::calcStrainMatrix(int ET, MatrixXd XY, int Li,int Lj, int Lm)
{
    MatrixXd B;

    double bi = XY(1,1) - XY(2,1);
    double bj = XY(2,1) - XY(0,1);
    double bm = XY(0,1) - XY(1,1);

    double ci = -XY(1,0) + XY(2,0);
    double cj = -XY(2,0) + XY(0,0);
    double cm = -XY(0,0) + XY(0,0);

    Matrix<double,3,3> DD;
    DD << 1,XY(0,0),XY(0,1),1,XY(1,0),XY(1,1),1,XY(2,0),XY(2,1);

    double S2 = DD.determinant();

    switch (ET) {
    case 3:
    {
        Matrix<double,3,2> Bi,Bj,Bm;
        B.resize(3,6);

        Bi << bi,0,0,ci,ci,bi;
        Bj << bj,0,0,cj,cj,bj;
        Bm << bm,0,0,cm,cm,bm;
        B << Bi,Bj,Bm;

        B = B / S2;
        break;
    }
    case 6:
    {
        Matrix<double,3,2> Bi, Bj, Bm, B1, B2, B3;
        B.resize(3,12);

        Bi << bi*(4*Li-1), 0,
              0,           ci*(4*Li-1),
              ci*(4*Li-1), bi*(4*Li-1);

        Bj << bj*(4*Lj-1), 0,
              0,           cj*(4*Lj-1),
              cj*(4*Lj-1), bj*(4*Lj-1);

        Bm << bm*(4*Lm-1), 0,
              0,           cm*(4*Lm-1),
              cm*(4*Lm-1), bm*(4*Lm-1);

        B1 << 4*(bj*Lm+Lj*bm), 0,
              0,               4*(cj*Lm+Lj*cm),
              4*(cj*Lm+Lj*cm), 4*(bj*Lm+Lj*bm);

        B2 << 4*(bm*Li+Lm*bi), 0,
              0,               4*(cm*Li+Lm*ci),
              4*(cm*Li+Lm*ci), 4*(bm*Li+Lm*bi);

        B3 << 4*(bi*Lj+Li*bj), 0,
              0,               4*(ci*Lj+Li*cj),
              4*(ci*Lj+Li*cj), 4*(bi*Lj+Li*bj);

        B << Bi,Bj,Bm,B1,B2,B3;

        B /= S2;
        break;
    }
    }
    return B;
}

void Model::createVTKResultFile()
{
    //生成结果数据文件到currentPath/Result

    int NNE = 3;
    int NN = this->NN;
    if (ET == 6)
         NN -= part[unsigned(PI)].NS;

    QString resultData;
    resultData.append("# vtk DataFile Version 2.0\n");
    resultData.append("FEM Result File\n");
    resultData.append("ASCII\n");
    resultData.append("DATASET UNSTRUCTURED_GRID\n");

    //POINTS
    resultData.append("\nPOINTS ");
    resultData.append(QString::number(NN));
    resultData.append(" double\n");
    for (int i = 0; i < NN; i++)
    {
        resultData.append(QString::number(CXY(i,0)) + QString(" "));
        resultData.append(QString::number(CXY(i,1)) + QString(" "));
        resultData.append("0\n");
    }

    //CELLS
    resultData.append("\nCELLS ");
    resultData.append(QString::number(NE) + QString(" "));
    resultData.append(QString::number(NE*(NNE+1)) + QString("\n"));
    for (int i = 0; i < NE; i++)
    {
        resultData.append(QString::number(NNE) + QString(" "));
        for (int j = 0; j < NNE; j++)
            resultData.append(QString::number(EN(i,j)) + QString(" "));
        resultData.append(QString("\n"));
    }

    //CELL_TYPES
    resultData.append("\nCELL_TYPES ");
    resultData.append(QString::number(NE) + QString("\n"));
    for (int i = 0; i < NE; i++)
        resultData.append(QString::number(5) + QString("\n"));

    //POINT_DATA
    resultData.append("\nPOINT_DATA ");
    resultData.append(QString::number(NN) + QString("\n"));
    resultData.append("\nSCALARS Coor(m) double 3\n");
    resultData.append("\nLOOKUP_TABLE default\n");
    for (int i = 0; i < NN; i++)
    {
        resultData.append(QString::number(CXY(i,0)) + QString(" "));
        resultData.append(QString::number(CXY(i,1)) + QString(" "));
        resultData.append("0\n");
    }

    //VECTORS displace
    resultData.append("\nVECTORS Displace double\n");
    for (int i = 0; i < NN; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (ID(i,j) == 0)
                resultData.append(QString::number(0) + QString(" "));
            else
                resultData.append(QString::number(qAbs(Delta(ID(i,j)-1))) + QString(" "));
        }
        resultData.append("0\n");
    }

    //Calculate Strain & Stress
    calcStrainStress();

/*
    //VECTORS STRESS
    resultData.append("\nVECTORS STRESS double\n");
    for (int i = 0; i < NN; i++)
    {
        for (int j = 0; j < 3; j++)
            resultData.append(QString::number(STRESS(i,j)) + QString(" "));
        resultData.append("\n");
    }

    //VECTORS STRAIN
    resultData.append("\nVECTORS STRESS double\n");
    for (int i = 0; i < NN; i++)
    {
        for (int j = 0; j < 3; j++)
            resultData.append(QString::number(STRAIN(i,j)) + QString(" "));
        resultData.append("\n");
    }
*/

    //SCALARS STRESS-X
    resultData.append("\nSCALARS STRESS_X double 1\n");
    resultData.append("LOOKUP_TABLE default\n");
    for (int i = 0; i < NN; i++)
        resultData.append(QString::number(qAbs(STRESS(i,0))) + QString("\n"));

    //SCALARS STRESS-Y
    resultData.append("\nSCALARS STRESS_Y double 1\n");
    resultData.append("LOOKUP_TABLE default\n");
    for (int i = 0; i < NN; i++)
        resultData.append(QString::number(qAbs(STRESS(i,1))) + QString("\n"));

    //SCALARS STRESS-XY
    resultData.append("\nSCALARS STRESS_XY double 1\n");
    resultData.append("LOOKUP_TABLE default\n");
    for (int i = 0; i < NN; i++)
        resultData.append(QString::number(qAbs(STRESS(i,2))) + QString("\n"));

    //SCALARS STRAIN_X
    resultData.append("\nSCALARS STRAIN_X double 1\n");
    resultData.append("LOOKUP_TABLE default\n");
    for (int i = 0; i < NN; i++)
        resultData.append(QString::number(qAbs(STRAIN(i,0))) + QString("\n"));

    //SCALARS STRAIN_Y
    resultData.append("\nSCALARS STRAIN_Y double 1\n");
    resultData.append("LOOKUP_TABLE default\n");
    for (int i = 0; i < NN; i++)
        resultData.append(QString::number(qAbs(STRAIN(i,1))) + QString("\n"));

    //SCALARS STRAIN_XY
    resultData.append("\nSCALARS STRAIN_XY double 1\n");
    resultData.append("LOOKUP_TABLE default\n");
    for (int i = 0; i < NN; i++)
        resultData.append(QString::number(qAbs(STRAIN(i,2))) + QString("\n"));

    //Write VTK Result File
    QByteArray resultDataByte = resultData.toUtf8();
    QDir *folder = new QDir;
    bool exist = folder->exists(QDir::currentPath()+QString("/Result"));
    if (!exist)
        folder->mkdir(QDir::currentPath()+QString("/Result"));

    QFile resultDataFile(QDir::currentPath()+QString("/Result/Result.vtk"));
    if (resultDataFile.exists())
        QFile::remove(QDir::currentPath()+QString("/Result/Result.vtk"));
    resultDataFile.open(QIODevice::WriteOnly|QIODevice::Text);
    resultDataFile.write(resultDataByte,resultDataByte.length());
    resultDataFile.close();

}

VectorXd Model::solveSystem()
{
    VectorXd Delta;
    MatrixXd GK;
    int NDF = 2,NNE = 3;
    if (ET == 3)   {NDF = 2;NNE = 3;}
    else if (ET == 6) {NDF = 2; NNE = 6;}
    GK = calcGK(ET,SM,MI,T);
    VectorXd NF;
    NF.resize(2*NN-IFIX.sum());
    for (int i = 0,j = 0; i < IFIX.size(); i++)
        if (!IFIX(i))  { NF(j) = F(i); j++;}
    switch (SM) {
    case 0:
        Delta = LU0(GK,NF);
        break;
    case 1:
    {
        VectorXi M = calcM(NDF,NNE,NE,NN,IFIX,EN);
        VectorXi AM = calcAM(NDF,NNE,NE,NN,IFIX,EN);
        Delta = LU1(GK,NF,M,AM);
        break;
    }
    case 2:
        Delta = LU2(GK,NF);
        break;
    }
    this->Delta = Delta;
    return Delta;
}
