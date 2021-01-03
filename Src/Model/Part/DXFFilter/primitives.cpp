#include "primitive.h"
#include <qmath.h>

Primitive::Primitive()
{

}

Primitive::~Primitive()
{

}

int Primitive::getType()
{
    return type;
}

QPointF Primitive::getBeginPoint()
{
    return beginPoint;
}

QPointF Primitive::getEndPoint()
{
    return endPoint;
}

QPointF Primitive::getCenterOfCircle()
{
    return centerOfCircle;
}

double Primitive::getRadius()
{
    return radius;
}

double Primitive::getBeginAngle()
{
    return beginAngle;
}

double Primitive::getEndAngle()
{
    return endAngle;
}

bool Primitive::getClosed()
{
    return closed;
}

void Primitive::setLine(QPointF BP, QPointF EP)
{
    type = 1;
    closed = false;

    beginPoint = BP;
    endPoint = EP;
}

void Primitive::setArc(QPointF C, double R, double BA, double EA)
{
    type = 2;
    closed = false;

    centerOfCircle = C;
    radius = R;
    beginAngle = BA;
    endAngle = EA;

    beginPoint.setX(C.x()+R*qCos(BA));
    beginPoint.setY(C.y()+R*qSin(BA));
    endPoint.setX(C.x()+R*qCos(EA));
    endPoint.setY(C.y()+R*qSin(EA));
}

void Primitive::setCircle(QPointF C, double R)
{
    type = 3;
    closed = true;

    centerOfCircle = C;
    radius = R;
}

void Primitive::setPrimitive(QPointF BP, QPointF EP, double BA, double EA)
{
    beginPoint = BP;
    endPoint = EP;
    beginAngle = BA;
    endAngle = EA;
}
