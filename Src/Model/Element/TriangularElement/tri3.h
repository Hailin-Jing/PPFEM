#ifndef TRI3_H
#define TRI3_H

#include "Eigen3/Eigen/Dense"
#include "femelement.h"
#include "material.h"

using namespace Eigen;

class TRI3 : public FEMElement
{

private:
    int NDF;
    int NNE;

public:
    TRI3();

    //计算单元刚度矩阵
    MatrixXd calcEK(MatrixXd coords,Material material,double thickness);
};

#endif // TRI3_H
