#ifndef BOUNDARYWINDOW_H
#define BOUNDARYWINDOW_H

#include <QtCharts>
#include <QMainWindow>
#include <vector>

#include "model.h"
#include "primitive.h"
#include "dxffilter.h"

using namespace QtCharts;

namespace Ui {
class BoundaryWindow;
}

class BoundaryWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *labXYVaulue;                               //坐标显示标签
    Model *model;                                      //模型指针
    int partIndex;                                     //部件索引
    std::vector<Primitive> PR;                         //几何图元
    DXFFilter *DXF;                                    //图元容器
    std::vector<std::vector<int>> SPI;                 //待选择的图元索引
    std::vector<std::vector<std::vector<int>>> CPI;    //闭合区域索引(顺时针)
    std::vector<std::vector<std::vector<int>>> RCPI;   //闭合区域索引(逆时针)

public:
    explicit BoundaryWindow(QWidget *parent = nullptr,Model *model = nullptr,DXFFilter *DXF = nullptr,
                                     int partIndex = 0,int windowType = 1);
    ~BoundaryWindow();

private slots:

    //坐标区视图相关槽函数
    void on_mouseMovePoint(QPoint point);
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionZoomReset_triggered();

    //选择边界
    void on_actionChooseBoundary_triggered();
    //取消选择
    void on_actionCancelSelect_triggered();
    //清空选择
    void on_actionReSelect_triggered();
    //添加边界条件
    void on_actionAddBoundaryCondition_triggered();
    //添加荷载
    void on_actionAddLoad_triggered();


private:
    Ui::BoundaryWindow *ui;
};

#endif // BOUNDARYWINDOW_H
