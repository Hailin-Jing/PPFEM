#ifndef MODEL_H
#define MODEL_H

#include "Eigen3/Eigen/Dense"
using namespace Eigen;

#include <vector>
#include <QString>
#include "material.h"
#include "part.h"
#include "tri3.h"
#include "tri6.h"

class Model
{
    int NN;                          // 结点总数
    int NE;                          // 单元总数
    int NS;                          // 边数
    MatrixXi EN;                     // 单元节点号
    MatrixXd CXY;                    // 节点坐标
    MatrixXi SI;                     // 边
    VectorXi IFIX;                   // 约束自由度
    VectorXd F;                      // 荷载列阵
    std::vector<Material> material;  // 材料
    std::vector<Part> part;          // 部件
    MatrixXd GK;                     // 总刚矩阵
    VectorXd Delta;                  // 节点位移

    int PT = 1;                      // 问题类型
    int ET = 3;                      // 单元类型
    double T = 1;                    // 模型厚度
    int SM = 1;                      // 存储方法
    int SLE = 1;                     // 求解方法
    int PI;                          // 部件号
    int MI;                          // 材料号

    int NBC = 0;                     // 边界条件数
    int NL = 0;                      // 荷载数

    MatrixXi ID;                     // 节点位移信息
    MatrixXi LM;                     // 连接矩阵
    VectorXi M;                      // 非零首行号
    VectorXi AM;                     // 辅助数组

    MatrixXd STRESS;                 // 应力
    MatrixXd STRAIN;                 // 应变

public:
    Model();
    ~Model();

    // 类访问接口
    // 单元
    void setElementNode(MatrixXi EN);
    void setElementNumber(int NE);
    MatrixXi getElementNode();
    int getElementNumber();

    // 节点
    void setNodeCoordinate(MatrixXd CXY);
    void setNodeNumber(int NN);
    MatrixXd getNodeCoordinate();
    int getNodeNumber();

    // 边
    void setSide(MatrixXi SI);
    void setSideNumber(int NS);
    MatrixXi getSide();
    int getSideNumber();

    // 约束自由度
    void setFixedDegree(VectorXi IFIX);
    VectorXi getFixedDegree();

    // 荷载
    void setLoad(VectorXd F);
    VectorXd getLoad();

    // 材料
    void addMaterial(Material M);
    void removeMaterial(int index);
    Material *getMaterial(int index);
    int getMaterialNumber();

    // 部件
    void addPart(Part P);
    void removePart(int index);
    Part *getPart(int index);
    void setPart(int index,Part P);
    int getPartNumber();

    // 边界条件数
    int getBoundaryConditionNumber();
    void addBoundaryConditionNumber(int N = 1);
    // 荷载数
    int getLoadNumber();
    void addLoadNumber(int N = 1);

    // 设置作业参数
    void setJobArgument(int PT,int ET,double T,int SM,int SLE,int PI,int MI);

    // 获取作业参数
    void getJobArgument(int &PT,int &ET,double &T,int &SM,int &SLE,int &PI,int &MI);
    int getElementType();

    // 三节点三角形单元数据转化为六节点三角形单元数据
    void TrigularElement3To6();

    // 节点位移信息矩阵
    MatrixXi calcID(int NDF, int NN, VectorXi IFIX);
    MatrixXi getID();
    // 连接矩阵
    MatrixXi calcLM(int NDF, int NNE, int NE,int NN,VectorXi IFIX, MatrixXi EN);
    MatrixXi getLM();
    // 非零首行号
    VectorXi calcM(int NDF, int NNE, int NE,int NN,VectorXi IFIX, MatrixXi EN);
    VectorXi getM();
    // 辅助数组
    VectorXi calcAM(int NDF, int NNE, int NE,int NN,VectorXi IFIX, MatrixXi EN);
    VectorXi getAM();
    // 计算总刚矩阵
    MatrixXd calcGK(int ET,int SM,int MI,double T);

    // 计算边界条件数据
    void calcBoundaryCondition();
    // 计算荷载数据
    void calcLoad();
    // 计算体力（自重）等效荷载
    void calcGravityLoad(int ET,MatrixXd CXY,MatrixXi EN,double Density,double GX,double GY,double T,VectorXd &Load);
    // 计算线性分布荷载
    void calcLinearDistributedLoad(int ET,MatrixXi SI,VectorXd &Load,VectorXd DL,double T);
    // 计算应变、应力
    void calcStrainStress();
    // 计算应变矩阵
    MatrixXd calcStrainMatrix(int ET,MatrixXd XY,int Li = 1,int Lj = 0, int Lm = 0);
    // 生成结果数据文件
    void createVTKResultFile();

    // 求解线性方程组
    VectorXd solveSystem();
};

#endif //  MODEL_H
