#ifndef PARTWINDOW_H
#define PARTWINDOW_H

#include <QtCharts>
#include <QMainWindow>
#include <QGraphicsScene>

#include "model.h"
#include "primitive.h"
#include "dxffilter.h"

using namespace QtCharts;

namespace Ui {
class PartWindow;
}

class PartWindow : public QMainWindow
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
    int argc;                                          //应用参数个数
    char **argv;                                       //应用参数
    QLineSeries **MS;                                  //网格系列
    int MSN;                                           //网格系列数

public:
    explicit PartWindow(QWidget *parent = nullptr,Model *model = nullptr,DXFFilter *DXF = nullptr,
                        int partIndex = 0,int argc = 0, char *[] =nullptr);
    ~PartWindow();

    int createMeshControlData(double,double);
        std::vector<std::vector<double>> createBoundaryNodes();
        std::vector<std::vector<std::vector<double>>> createHoleNodes();
        std::vector<std::vector<double>> createNodes(unsigned int,int);
        double length(int);
        bool saveMeshData();
        void drawMesh();

private slots:

    //坐标区视图相关槽函数
    void on_mouseMovePoint(QPoint point);
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionZoomReset_triggered();

    //定义边界
    void on_actionBoundary_triggered();
    //新建孔洞
    void on_actionHoleNew_triggered();
    //取消选择
    void on_actionCancelSelect_triggered();
    //清空选择
    void on_actionReSelect_triggered();
    //确认导入
    void on_actionOK_triggered();
    //查看已建模型
    void on_actionSubmittedModel_triggered();
    //生成模型控制数据
    void on_actionModelControlData_triggered();
    //划分网格
    void on_actionMesh_triggered();
    //清除网格
    void on_actionClearMesh_triggered();

private:
    Ui::PartWindow *ui;
};

#endif // PARTWINDOW_H
