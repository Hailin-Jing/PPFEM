#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QPointF>

class Primitive
{
private:
    int type;                //图元类型：1为直线，2为圆弧，3为圆，4为矩形，5为多边形
    QPointF beginPoint;      //起始点
    QPointF endPoint;        //结束点
    QPointF centerOfCircle;  //圆心
    double radius;           //圆弧半径
    double beginAngle;       //起始角
    double endAngle;         //终止角
    bool closed = false;     //是否闭合
public:
    Primitive();
    ~Primitive();

    //获取图元参数
    int getType();
    QPointF getBeginPoint();
    QPointF getEndPoint();
    QPointF getCenterOfCircle();
    double getRadius();
    double getBeginAngle();
    double getEndAngle();
    bool getClosed();

    //设置图元参数
    void setLine(QPointF,QPointF);
    void setArc(QPointF,double,double,double);
    void setCircle(QPointF,double);
    void setPrimitive(QPointF,QPointF,double,double);
};

#endif // PRIMITIVE_H
