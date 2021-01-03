#include "qwchartview.h"
#include <iostream>

const double Pi = 3.14159265358979323846264338328;

QWChartView::QWChartView(QWidget *parent):QChartView(parent)
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setMouseTracking(true);
}

void QWChartView::iniChartView
(std::vector<Primitive> PR, std::vector<std::vector<int> > SPI,std::vector<double> range)
{
    this->PR = PR;
    this->SPI = SPI;
    lineSeries = new QLineSeries *[int(PR.size())];

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    for (unsigned int i = 0; i < PR.size(); i++)
    {
        lineSeries[i] = new QLineSeries();
        if (PR[i].getType() == 3) //圆
        {
            QPointF C = PR[i].getCenterOfCircle();
            double R = PR[i].getRadius();
            int nodes = 100;
            for (int j = 0; j <= nodes; j++)
            {
                lineSeries[i]->append(C.x()+R*qCos(2*Pi*j/nodes),C.y()+R*qSin(2*Pi*j/nodes));
                lineSeries[i]->setPen(pen);
            }
            lineSeries[i]->setPen(pen);
            chart()->addSeries(lineSeries[i]);
            continue;
        }
        else if (PR[i].getType() == 1)  //直线
        {
            lineSeries[i]->append(PR[i].getBeginPoint());
            lineSeries[i]->append(PR[i].getEndPoint());
            lineSeries[i]->setPen(pen);
            chart()->addSeries(lineSeries[i]);
            continue;
        }
    }
    chart()->createDefaultAxes();
    auto axisx = chart()->axes(Qt::Horizontal);
    auto axisy = chart()->axes(Qt::Vertical);
    QAbstractAxis *axisX = axisx.at(0);
    QAbstractAxis *axisY = axisy.at(0);
    axisX->setRange(range[0],range[1]);
    axisY->setRange(range[2],range[3]);
    chart()->legend()->setVisible(false);
}

void QWChartView::mousePressEvent(QMouseEvent *event)
{//鼠标左键按下，记录beginPoint
    if (event->button() == Qt::LeftButton)
        beginPoint=event->pos();
    QChartView::mousePressEvent(event);

}

void QWChartView::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动事件
    QPoint  point;
    point=event->pos();
    emit mouseMovePoint(point);
    QChartView::mouseMoveEvent(event);

}

void QWChartView::mouseReleaseEvent(QMouseEvent *event)
{
    endPoint=event->pos();

    if (CM == 1)  //选择模式
        choosePrimitive();
    else if (CM == 2)  //取消选择模式
        cancelChoosePrimitive();

    if (event->button()==Qt::LeftButton)
    { //鼠标左键释放，获取矩形框的endPoint,进行缩放

        QRectF  rectF;
        rectF.setTopLeft(this->beginPoint);
        rectF.setBottomRight(this->endPoint);
        this->chart()->zoomIn(rectF);

        if (windowRectF == nullptr)
            windowRectF = new QRectF();

        windowRectF->setTopLeft(this->beginPoint);
        windowRectF->setBottomRight(this->endPoint);
    }
    else if (event->button()==Qt::RightButton)
    {
        this->chart()->zoomReset(); //鼠标右键释放，resetZoom
        windowRectF = nullptr;
        ZoomFactor = 1;
        Key_X_Scroll = 0;
        Key_Y_Scroll = 0;
    }
    QChartView::mouseReleaseEvent(event);
}

bool QWChartView::primitiveAllInRect(std::vector<Primitive> PR,int PI, QPointF PF1,QPointF PF2)
{
    Primitive P = PR[unsigned(PI)];
    bool in = true;
    if (P.getType() == 1) //直线
    {
        QPointF BP = P.getBeginPoint();
        QPointF EP = P.getEndPoint();
        if (BP.x() < qMin(PF1.x(),PF2.x()) ||
            BP.x() > qMax(PF1.x(),PF2.x()) ||
            BP.y() < qMin(PF1.y(),PF2.y()) ||
            BP.y() > qMax(PF1.y(),PF2.y()) ||
            EP.x() < qMin(PF1.x(),PF2.x()) ||
            EP.x() > qMax(PF1.x(),PF2.x()) ||
            EP.y() < qMin(PF1.y(),PF2.y()) ||
            EP.y() > qMax(PF1.y(),PF2.y()) )
            in = false;
    }
    else if (P.getType() == 2)  //弧线
    {
        const double pi = 3.14159265358979323846;
        QPointF C = P.getCenterOfCircle();
        double R = P.getRadius();
        double beginAngle = P.getBeginAngle();
        double endAngle = P.getEndAngle();
        double maxAngleAbs = qMax(qAbs(beginAngle),qAbs(endAngle));
        double minAngleAbs = qMin(qAbs(beginAngle),qAbs(endAngle));
        double maxAnglePositive;
        double maxAngleNegative;
        if (qAbs(beginAngle - pi/2) < qAbs(endAngle - pi/2))
            maxAnglePositive = beginAngle;
        else
            maxAnglePositive = endAngle;
        if (qAbs(beginAngle + pi/2) < qAbs(endAngle + pi/2))
            maxAngleNegative = beginAngle;
        else
            maxAngleNegative = endAngle;
        if (C.x() + R * qCos(maxAngleAbs) <qMin(PF1.x(),PF2.x()) ||
            C.x() + R * qCos(minAngleAbs) > qMax(PF1.x(),PF2.x()) ||
            C.y() + R * qCos(maxAngleNegative) < qMin(PF1.y(),PF2.y()) ||
            C.y() + R * qCos(maxAnglePositive) > qMax(PF1.y(),PF2.y()))
            in = false;
    }
    else if (P.getType() == 3)  //圆
    {
        double R = P.getRadius();
        QPointF C = P.getCenterOfCircle();
        if (C.x() - R < qMin(PF1.x(),PF2.x()) ||
            C.x() + R > qMax(PF1.x(),PF2.x()) ||
            C.y() - R < qMin(PF1.y(),PF2.y()) ||
            C.y() + R > qMax(PF1.y(),PF2.y()))
            in = false;
    }
    return in;
}

bool QWChartView::primitiveAnyInRect(std::vector<Primitive> PR,int PI, QPointF PF1,QPointF PF2)
{
    Primitive P = PR[unsigned(PI)];
    bool in = false;
    if (P.getType() == 1) //直线
    {
        QPointF BP = P.getBeginPoint();
        QPointF EP = P.getEndPoint();
        QPointF PF3 = QPointF(PF1.x(),PF2.y());
        QPointF PF4 = QPointF(PF2.x(),PF1.y());

        if (lineCrossLine(BP,EP,PF1,PF3) ||
            lineCrossLine(BP,EP,PF1,PF4) ||
            lineCrossLine(BP,EP,PF2,PF3) ||
            lineCrossLine(BP,EP,PF2,PF4) ||
            primitiveAllInRect(PR,PI,PF1,PF2))
            in = true;
    }
    else if (P.getType() == 2)  //弧线
    {
        const double pi = 3.14159265358979323846;
        QPointF C = P.getCenterOfCircle();
        double R = P.getRadius();
        double beginAngle = P.getBeginAngle();
        double endAngle = P.getEndAngle();
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
        if ((C.x() + R * qCos(maxAngleAbs) >qMin(PF1.x(),PF2.x()) &&
             C.x() + R * qCos(minAngleAbs) < qMax(PF1.x(),PF2.x()) )||
            (C.y() + R * qCos(maxAngleNegative) > qMin(PF1.y(),PF2.y()) &&
             C.y() + R * qCos(maxAnglePositive) < qMax(PF1.y(),PF2.y())) )
            in = true;
    }
    else if (P.getType() == 3)  //圆
    {
        double R = P.getRadius();
        QPointF C = P.getCenterOfCircle();
        QPointF PF3 = QPointF(PF1.x(),PF2.y());
        QPointF PF4 = QPointF(PF1.y(),PF2.x());
        if (lineCrossCircle(PF1,PF3,C,R) ||
            lineCrossCircle(PF1,PF4,C,R) ||
            lineCrossCircle(PF2,PF3,C,R) ||
            lineCrossCircle(PF2,PF4,C,R) ||
            primitiveAllInRect(PR,PI,PF1,PF2))
            in = true;
    }
    return in;
}

bool QWChartView::PlineAllInRect(std::vector<Primitive> PR,std::vector<int> PI, QPointF PF1, QPointF PF2)
{
    bool in = true;
    for (unsigned int i = 0; i < PI.size(); i++)
    {
        if (!primitiveAllInRect(PR,PI[i],PF1,PF2))
        {
            in  = false;
            break;
        }
    }
    return in;
}

bool QWChartView::PlineAnyInRect(std::vector<Primitive> PR,std::vector<int> PI, QPointF PF1, QPointF PF2)
{
    bool in = false;
    for (unsigned int i = 0; i < PI.size(); i++)
    {
        if (primitiveAnyInRect(PR,PI[i],PF1,PF2))
        {
            in  = true;
            break;
        }
    }
    return in;
}

bool QWChartView::lineCrossLine(QPointF P11, QPointF P12, QPointF P21, QPointF P22)
{
    double A1,B1,C1,A2,B2,C2;
    A1 = P12.y() - P11.y();
    B1 = P11.x() - P12.x();
    C1 = -A1 * P11.x() - B1 * P11.y();
    A2 = P22.y() - P21.y();
    B2 = P21.x() - P22.x();
    C2 = -A2 * P21.x() - B2 * P21.y();
    double D = A1 * B2 - A2 * B1;
    if (qAbs(D) < 0.000001)
        return false;
    double D1 = -C1 * B2 + B1 * C2;
    double D2 = -A1 * C2 + C1 * A2;
    double x = D1 / D;
    double y = D2 / D;
    double x11 = qMin(P11.x(),P12.x());
    double x12 = qMax(P11.x(),P12.x());
    double x21 = qMin(P21.x(),P22.x());
    double x22 = qMax(P21.x(),P22.x());
    double y11 = qMin(P11.y(),P12.y());
    double y12 = qMax(P11.y(),P12.y());
    double y21 = qMin(P21.y(),P22.y());
    double y22 = qMax(P21.y(),P22.y());
    if (x >= qMax(x11,x21) && x <= qMin(x12,x22) &&
        y >= qMax(y11,y21) && y <= qMin(y12,y22) )
        return true;
    else
        return false;
}

bool QWChartView::lineCrossCircle(QPointF BP, QPointF EP, QPointF C, double R)
{
    double D1 = sqrt(qPow(C.x()-BP.x(),2)+qPow(C.y()-BP.y(),2));
    double D2 = sqrt(qPow(C.x()-EP.x(),2)+qPow(C.y()-EP.y(),2));
    if ((D1-R) * (D2-R) <= 0)
        return true;
    else if (D1 < R && D2 < R)
        return false;
    else
        if (qMin(D1,D2) <= R)
            return true;
        else
            return false;

}

void QWChartView::choosePrimitive()
{
    QPointF beginpoint = chart()->mapToValue(beginPoint);
    QPointF endpoint = chart()->mapToValue(endPoint);
    QPen pen;
    pen.setWidth(2);

    if (beginpoint.x() < endpoint.x())  //窗口选择
    {
        for (int i = 0; i < int(SPI.size()); i++)
            if (PlineAllInRect(PR,SPI[unsigned(i)],beginpoint,endpoint))
            {
                CP.push_back(i);
                changeLineSeriesColor(i,Qt::red);
            }
    }
    else  //窗交选择
    {
        for (int i = 0; i < int(SPI.size()); i++)
            if (PlineAnyInRect(PR,SPI[unsigned(i)],beginpoint,endpoint))
            {
                CP.push_back(i);
                changeLineSeriesColor(i,Qt::red);
            }
    }
}

void QWChartView::cancelChoosePrimitive()
{
    QPointF beginpoint = chart()->mapToValue(beginPoint);
    QPointF endpoint = chart()->mapToValue(endPoint);
    QPen pen;
    pen.setWidth(2);

    if (beginpoint.x() < endpoint.x())  //窗口选择
    {
        for (int i = 0; i < int(CP.size()); i++)
            if (PlineAllInRect(PR,SPI[unsigned(CP[unsigned(i)])],beginpoint,endpoint))
            {
                CP.erase(CP.begin()+i);
                changeLineSeriesColor(CP[unsigned(i)],Qt::black);
            }
    }
    else  //窗交选择
    {
        for (int i = 0; i < int(CP.size()); i++)
            if (PlineAnyInRect(PR,SPI[unsigned(CP[unsigned(i)])],beginpoint,endpoint))
            {
                CP.erase(CP.begin()+i);
                changeLineSeriesColor(CP[unsigned(i)],Qt::black);
            }
    }
}

void QWChartView::changeLineSeriesColor(int PI, QColor color)
{
    for (int i = 0; i < int(SPI[unsigned(PI)].size()); i++)
    {
        QPen pen = lineSeries[SPI[unsigned(PI)][unsigned(i)]]->pen();
        pen.setColor(color);
        lineSeries[SPI[unsigned(PI)][unsigned(i)]]->setPen(pen);
    }
}

void QWChartView::iniLineSeriesColor()
{
    for (int i = 0; i < int(PR.size()); i++)
    {
        QPen pen = lineSeries[i]->pen();
        pen.setColor(Qt::black);
        lineSeries[i]->setPen(pen);
    }
    if (CP.size() > 0)
        CP.erase(CP.begin(),CP.end());
    CP.erase(CP.begin(),CP.end());
}

void QWChartView::setLineSeriesColor(std::vector<int> index, std::vector<QColor> color)
{
    for (unsigned int i = 0; i < index.size(); i++)
    {
        QPen pen = lineSeries[index[i]]->pen();
        pen.setColor(color[unsigned(i)]);
        for (unsigned int j = 0; j < SPI[i].size(); j++)
            lineSeries[unsigned(SPI[unsigned(index[i])][j])]->setPen(pen);
    }
}

std::vector<int> QWChartView::getChosenPrimitive()
{
    return CP;
}

void QWChartView::keyPressEvent(QKeyEvent *event)
{//按键控制
    switch (event->key())
    {
    case Qt::Key_Plus:
        chart()->zoom(1.2);      ZoomFactor   *= 1.2; break;
    case Qt::Key_Minus:
        chart()->zoom(0.8);      ZoomFactor   *= 0.8; break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0); Key_X_Scroll -= 10;  break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);  Key_X_Scroll += 10;  break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);  Key_Y_Scroll += 10;  break;
    case Qt::Key_Down:
        chart()->scroll(0, -10); Key_Y_Scroll -= 10;  break;
    case Qt::Key_PageUp:
        chart()->scroll(0, 50);  Key_Y_Scroll += 50;  break;
    case Qt::Key_PageDown:
        chart()->scroll(0, -50); Key_Y_Scroll -= 50;  break;
    case Qt::Key_Home:
        chart()->zoomReset();
        windowRectF = nullptr;
        ZoomFactor = 1;
        Key_X_Scroll = 0;
        Key_Y_Scroll = 0;
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

QWChartView:: ~QWChartView()
{

}

void QWChartView::setChooseMode(int CM)
{
    this->CM = CM;
}

void QWChartView::setZoomFactor(double ZF)
{
    ZoomFactor = ZF;
}

double QWChartView::getZoomFactor()
{
    return ZoomFactor;
}
