#ifndef QWCHARTVIEW_H
#define QWCHARTVIEW_H

#include <vector>
#include "primitive.h"
#include "dxffilter.h"

#include <QtCharts>  //必须这么设置
QT_CHARTS_USE_NAMESPACE     //必须这么设置

class QWChartView : public QChartView
{
    Q_OBJECT

private:
    //鼠标选择区域
    QPoint  beginPoint; //选择矩形区的起点
    QPoint  endPoint;  //选择矩形区的终点

    //图表缩放参数
    double ZoomFactor = 1;
    double Key_X_Scroll = 0;
    double Key_Y_Scroll = 0;
    QRectF  *windowRectF = nullptr;

    std::vector<Primitive> PR;                     //几何图元
    std::vector<std::vector<int>> SPI;             //待选择的图元索引
                                                   /*第一个索引为待选择的图元集合序号
                                                    *第二个索引为图元号*/
    std::vector<int> CP;                           //已选择图元集合序号
    int CM = 0;                                    //是否处于选择模式
                                                   /* CM = 0 表示未处于选择模式
                                                    * CM = 1 表示处于选择模式
                                                    * CM = 2 表示处于取消选择模式*/

    QLineSeries **lineSeries = nullptr;  //直线系列

public:
    explicit QWChartView(QWidget *parent = nullptr);
    void iniChartView(std::vector<Primitive> PR,std::vector<std::vector<int>> SPI,std::vector<double> range);
    ~QWChartView();

    //设置选择模式
    void setChooseMode(int CM);

    //坐标区缩放、平移因子
    void setZoomFactor(double);
    double getZoomFactor();

    //改变图元颜色
    void changeLineSeriesColor(int PI,QColor color);
    //图元颜色初始化
    void iniLineSeriesColor();
    //设置指定图元颜色
    void setLineSeriesColor(std::vector<int> index,std::vector<QColor> color);
    //获取选择图元信息
    std::vector<int> getChosenPrimitive();

protected:

    //鼠标事件
    void mousePressEvent(QMouseEvent *event);     //鼠标左键按下
    void mouseMoveEvent(QMouseEvent *event);      //鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);   //鼠标释放左键
    void keyPressEvent(QKeyEvent *event);         //键盘按键事件

    //计算几何函数
    bool primitiveAllInRect(std::vector<Primitive> PR,int PI, QPointF PF1,QPointF PF2);
    bool primitiveAnyInRect(std::vector<Primitive> PR,int PI, QPointF PF1,QPointF PF2);
    bool PlineAllInRect(std::vector<Primitive> PR,std::vector<int> PI, QPointF PF1, QPointF PF2);
    bool PlineAnyInRect(std::vector<Primitive> PR,std::vector<int> PI, QPointF PF1, QPointF PF2);
    bool lineCrossLine(QPointF P11, QPointF P12, QPointF P21, QPointF P22);
    bool lineCrossCircle(QPointF BP, QPointF EP, QPointF C, double R);

    //选择图元对象
    void choosePrimitive();
    void cancelChoosePrimitive();

signals:
    void mouseMovePoint(QPoint point); //鼠标移动信号，在mouseMoveEvent()事件中触发
};

#endif // QWCHARTVIEW_H
