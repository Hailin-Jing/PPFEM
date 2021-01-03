#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Eigen3/Eigen/Dense"
using namespace Eigen;
#include <QMainWindow>
#include <QProgressDialog>
#include <iostream>
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    int argc;                                          //应用参数个数
    char **argv;                                       //应用参数
    Model *model;                                      //模型指针

public:
    explicit MainWindow(QWidget *parent = nullptr,int argc = 0,char **argv = nullptr);
    ~MainWindow();

    void createManager(QString title, QStringList headerText,
                       std::vector<std::vector<QString>> data,
                       std::vector<bool> editable);
    //外部调用函数
    void NewMaterial();
    void NewPart();
    void NewBoundaryCondition();
    void NewLoad();

    //三节点三角形单元数据转化为六节点三角形单元数据
//    void TrigularElement3To6(int PI);

private slots:

    //新建部件
    void on_actionNewPart_triggered();
    //新建材料
    void on_actionNewMaterial_triggered();
    //新建边界条件
    void on_actionNewBoundaryCondition_triggered();
    //新建荷载
    void on_actionNewLoad_triggered();
    //部件管理器
    void on_actionPartManager_triggered();
    //材料管理器
    void on_actionMaterialManager_triggered();
    //边界条件管理器
    void on_actionBoundaryConditionManager_triggered();
    //荷载管理器
    void on_actionLoadManager_triggered();
    //作业参数
    void on_actionJob_triggered();
    //运行分析
    void on_actionAnalyze_triggered();

    //单元信息
    void on_actionElementNodeNumber_triggered();
    //节点信息
    void on_actionNodeCoordinate_triggered();
    //约束信息
    void on_actionFixedDegree_triggered();
    //荷载信息
    void on_actionLoad_triggered();
    //节点位移信息
    void on_actionID_triggered();
    //连接数组
    void on_actionLM_triggered();
    //辅助数组
    void on_actionAssistentMatrix_triggered();
    //每列首个非零元素索引
    void on_actionFirstNomzeroRow_triggered();
    //创建数据Tab
    void createDataVisualization(QString tabName,QStringList headerText,MatrixXd data);
    //结果输出
    void on_actionResult_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
