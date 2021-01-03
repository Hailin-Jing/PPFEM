#include "dxffilter.h"
#include "qmath.h"

DXFFilter::DXFFilter()
{

}

void DXFFilter::addLine(const DL_LineData &Line)
{
    primitiveNmuber = primitiveNmuber + 1;
    primitives.resize(unsigned(primitiveNmuber));

    std::vector<Primitive>::iterator it = primitives.begin();
    it[primitiveNmuber-1].setLine(QPointF(Line.x1,Line.y1),QPointF(Line.x2,Line.y2));

    if (qMin(Line.x1,Line.x2) < minX)
        minX = qMin(Line.x1,Line.x2);
    if (qMax(Line.x1,Line.x2) > maxX)
        maxX = qMax(Line.x1,Line.x2);
    if (qMin(Line.y1,Line.y2) < minY)
        minY = qMin(Line.y1,Line.y2);
    if (qMax(Line.y1,Line.y2) > maxY)
        maxY = qMax(Line.y1,Line.y2);
}

void DXFFilter::addArc(const DL_ArcData &Arc)
{
    primitiveNmuber = primitiveNmuber + 1;
    primitives.resize((unsigned(primitiveNmuber)));

    std::vector<Primitive>::iterator it = primitives.begin();
    it[primitiveNmuber-1].setArc(QPointF(Arc.cx,Arc.cy),Arc.radius,Arc.angle1,Arc.angle2);

    const double pi = 3.14159265358979323846;

    double beginAngle = Arc.angle1;
    double endAngle = Arc.angle2;

    double maxAngleAbs = qMax(qAbs(beginAngle),qAbs(endAngle));
    double minAngleAbs = qMin(qAbs(beginAngle),qAbs(endAngle));
    double maxAnglePositive;
    double maxAngleNegative;
    if (qAbs(beginAngle - pi/2) < qAbs(endAngle - pi/2))
        maxAnglePositive = beginAngle;
    else
        maxAnglePositive = endAngle;
    if (qAbs(beginAngle - 3*pi/2) < qAbs(endAngle - 3*pi/2))
        maxAngleNegative = beginAngle;
    else
        maxAngleNegative = endAngle;
    if (Arc.cx + Arc.radius * qCos(minAngleAbs) < minX)
        minX = Arc.cx + Arc.radius *qCos(minAngleAbs);
    if (Arc.cx + Arc.radius * qCos(maxAngleAbs) > maxX)
        maxX = Arc.cx + Arc.radius * qCos(maxAngleAbs);
    if (Arc.cy + Arc.radius * qSin(maxAngleNegative) < minX)
        minX = Arc.cy + Arc.radius * qSin(maxAngleNegative);
    if (Arc.cy + Arc.radius * qSin(maxAnglePositive) > maxX)
        maxX = Arc.cy + Arc.radius * qSin(maxAnglePositive);
}

void DXFFilter::addCircle(const DL_CircleData &Circle)
{
    primitiveNmuber = primitiveNmuber + 1;
    primitives.resize(unsigned(primitiveNmuber));

    std::vector<Primitive>::iterator it = primitives.begin();
    it[primitiveNmuber-1].setCircle(QPointF(Circle.cx,Circle.cy),Circle.radius);

    if (Circle.cx - Circle.radius < minX)
        minX = Circle.cx - Circle.radius;
    if (Circle.cx + Circle.radius > maxX)
        maxX = Circle.cx + Circle.radius;
    if (Circle.cy - Circle.radius < minY)
        minY = Circle.cy - Circle.radius;
    if (Circle.cy + Circle.radius > maxY)
        maxY = Circle.cy + Circle.radius;
}

int DXFFilter::getPrimitiveNmuber()
{
    return primitiveNmuber;
}

std::vector<Primitive> DXFFilter::getPrimitives()
{
    return primitives;
}

std::vector<std::vector<std::vector<int>>> DXFFilter::getCPI(int direction)
{
    unsigned int CPN = 0;  //closedPrimitivesNumber
    std::vector<std::vector<std::vector<int>>> tempCPI;
    std::vector<std::vector<std::vector<int>>> CPI;  //closedPrimitivesIndex
    std::vector<Primitive>::iterator it = primitives.begin();
    int *chosenIndex = new int[primitiveNmuber]();
    int *tempChosenIndex = new int[primitiveNmuber]();
    unsigned int chosenNumber = 0;
    unsigned int tempPrimitiveNmuber = 0;
    unsigned int tempCoordinatesNumber = 0;
    for (int i = 0; i < primitiveNmuber && chosenNumber < unsigned(primitiveNmuber); i++)
    {
        if (chosenIndex[i] == 1)
            continue;
        if (it[i].getClosed())
        {
            CPI.resize(unsigned(CPN+1));
            CPI[CPN].resize(2);
            CPI[CPN][0].resize(1);
            CPI[CPN][1].resize(1);
            CPI[CPN][0][0] = i;
            CPI[CPN][1][0] = 1;
            CPN = CPN + 1;
            chosenIndex[i] = 1;
            continue;
        }
        QPointF firstPoint = it[i].getBeginPoint();
        QPointF currentPoint = it[i].getEndPoint();
        std::cout<<"firstPoint:"<<firstPoint.x()<<","<<firstPoint.y()<<std::endl;
        std::cout<<"currentPoint:"<<currentPoint.x()<<","<<currentPoint.y()<<std::endl;
        tempChosenIndex = copy(chosenIndex,primitiveNmuber);
        if (CPN > 0)
            tempCPI = CPI;
        tempCPI.resize(CPN+1);
        tempCPI[CPN].resize(2);
        tempCPI[CPN][0].resize(1);
        tempCPI[CPN][1].resize(1);
        tempCPI[CPN][0][0] = i;
        tempCPI[CPN][1][0] = 1;
        std::vector<std::vector<double>> tempCoordinates;
        tempPrimitiveNmuber = 1;
        tempCoordinatesNumber = 0;
        for (;;)
        {
            //找到闭合路线
            if (currentPoint == firstPoint)
            {
//                std::cout<<"find closed primitive"<<std::endl;
                CPI = tempCPI;
                chosenIndex = tempChosenIndex;
//                std::cout<<"direction="<<direction<<std::endl;
//                std::cout<<"directionPolygen="<<directionPolygen(tempCoordinates)<<std::endl;
                if (direction != directionPolygen(tempCoordinates))
                    CPI[CPN] = reverse(CPI[CPN]);
                CPN = CPN + 1;
                chosenNumber += tempPrimitiveNmuber;
                break;
            }
            //寻找下一个匹配点
            bool exist = false;
            int index = i;
            bool dir = false;
            for (int j = 0; j < primitiveNmuber; j++)
            {
                if (tempChosenIndex[j] == 1  || j == index || it[j].getClosed())
                    continue;
                if (it[j].getBeginPoint() == currentPoint)
                {
                    exist = true;
                    index = j;
                    dir = false;
                    break;
                }
                else if (it[j].getEndPoint() == currentPoint)
                {
                    exist = true;
                    index = j;
                    dir = true;
                    break;
                }
            }
            //未找到匹配点
            if (!exist)
            {
//                std::cout<<"dont find point"<<std::endl;
                break;
            }
            //找到匹配点
//            std::cout<<"find Point"<<std::endl;
            tempChosenIndex[index] = 1;
            tempCPI.resize(CPN+1);
            tempCPI[CPN].resize(2);
            tempCPI[CPN][0].resize(tempPrimitiveNmuber+1);
            tempCPI[CPN][1].resize(tempPrimitiveNmuber+1);
            tempCPI[CPN][0][tempPrimitiveNmuber] = index;
            tempCoordinates.resize(tempCoordinatesNumber+2);
            tempCoordinates[tempCoordinatesNumber].resize(2);
            tempCoordinates[tempCoordinatesNumber+1].resize(2);
            if (!dir)
            {
                tempCPI[CPN][1][tempPrimitiveNmuber] = 1;
                currentPoint = it[index].getEndPoint();
                tempCoordinates[tempCoordinatesNumber][0] = currentPoint.x();
                tempCoordinates[tempCoordinatesNumber][1] = currentPoint.y();
                tempCoordinates[tempCoordinatesNumber+1][0] = it[index].getBeginPoint().x();
                tempCoordinates[tempCoordinatesNumber+1][1] = it[index].getBeginPoint().y();
            }
            else
            {
                tempCPI[CPN][1][tempPrimitiveNmuber] = 2;
                currentPoint = it[index].getBeginPoint();
                tempCoordinates[tempCoordinatesNumber][0] = currentPoint.x();
                tempCoordinates[tempCoordinatesNumber][1] = currentPoint.y();
                tempCoordinates[tempCoordinatesNumber+1][0] = it[index].getEndPoint().x();
                tempCoordinates[tempCoordinatesNumber+1][1] = it[index].getEndPoint().y();
            }
//            std::cout<<"currentPoint:"<<currentPoint.x()<<","<<currentPoint.y()<<std::endl;
            tempPrimitiveNmuber = tempPrimitiveNmuber + 1;
            tempCoordinatesNumber = tempCoordinatesNumber + 2;
        }
    }
    std::cout<<"Calculation Complete"<<std::endl;
    return CPI;
}

int *DXFFilter::copy(int *Index, int n)
{
    int *newIndex = new int[n];
    for (int i = 0; i < n; i++)
        newIndex[i] = Index[i];
    return newIndex;
}

int DXFFilter::directionPolygen(std::vector<std::vector<double>> Polygen)
{
    int nCount = int(Polygen.size());
    int direction;
    double S = 0;
    for (int i = 0; i < nCount - 1; i++)
        S += 0.5 *(Polygen[unsigned(i+1)][1]+Polygen[unsigned(i)][1])
                *(Polygen[unsigned(i+1)][0]-Polygen[unsigned(i)][0]);
    if (S < 0)  //顺时针
        direction = 1;
    else  //逆时针
        direction = 2;
    return direction;
}

std::vector<std::vector<int>> DXFFilter::reverse(std::vector<std::vector<int>> Polygen)
{
    int nCount = int(Polygen[1].size());
    Primitive primitive1,primitive2;
    for (int i = 0; i < nCount/2; i++)
    {
        int tempX = Polygen[0][unsigned(i)];
        int tempY = Polygen[1][unsigned(i)];
        Polygen[0][unsigned(i)] = Polygen[0][unsigned(nCount-i-1)];
        Polygen[1][unsigned(i)] = Polygen[1][unsigned(nCount-i-1)];
        Polygen[0][unsigned(nCount-i-1)] = tempX;
        Polygen[1][unsigned(nCount-i-1)] = tempY;
        primitive1 = primitives[unsigned(Polygen[0][unsigned(i)])];
        primitives[unsigned(Polygen[0][unsigned(i)])].setPrimitive(
                    primitive1.getEndPoint(),primitive1.getBeginPoint(),
                    primitive1.getEndAngle(),primitive1.getBeginAngle());
        primitive2 = primitives[unsigned(Polygen[0][unsigned(nCount-i-1)])];
        primitives[unsigned(Polygen[0][unsigned(nCount-i-1)])].setPrimitive(
                    primitive2.getEndPoint(),primitive2.getBeginPoint(),
                    primitive2.getEndAngle(),primitive2.getBeginAngle());

    }
    return Polygen;
}

std::vector<double> DXFFilter::getRange()
{
    std::vector<double> range;
    range.resize(4);
    range[0] = minX - (maxX-minX)/10;
    range[1] = maxX + (maxX-minX)/10;
    range[2] = minY - (maxY-minY)/10;
    range[3] = maxY + (maxY-minY)/10;
    return range;
}
