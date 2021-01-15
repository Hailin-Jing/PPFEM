#ifndef TRI6_H
#define TRI6_H

#include "Eigen3/Eigen/Dense"
#include "femelement.h"
#include "material.h"

using namespace Eigen;

class TRI6 :public FEMElement
{

private:
    int NDF;
    int NNE;

public:
    TRI6();

    //计算单元刚度矩阵
    MatrixXd calcEK(MatrixXd coords,Material material,double thickness);
};

#endif // TRI6_H
