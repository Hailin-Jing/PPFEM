#ifndef PART_H
#define PART_H
#include "Eigen3/Eigen/Dense"
using namespace Eigen;
#include "bc.h"
#include "load.h"
#include "dxffilter.h"
#include <QString>
#include <vector>

class Part
{
public:
    DXFFilter *DXF;                      //图元容器
    QString PN;                          //部件名
    int BCPI = -1;                       //外边界图元索引
    std::vector<int> HCPI;               //孔洞图元索引
    MatrixXi EN;                         //单元节点号
    MatrixXd EC;                         //单元形心坐标
    MatrixXd CXY;                        //节点坐标
    MatrixXi SI;                         //边

    std::vector<BC> BC; //边界条件数据
    std::vector<LOAD> F;  //荷载数据

    int NH;                              //孔洞数量
    int NN;                              //节点数量
    int NE;                              //单元数量
    int NS;                              //边的数量

    Part(QString PN);
};

#endif // PART_H
