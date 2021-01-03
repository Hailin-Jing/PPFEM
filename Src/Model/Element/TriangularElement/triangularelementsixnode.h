#ifndef TRIANGULARELEMENTSIXNODE_H
#define TRIANGULARELEMENTSIXNODE_H

#include "Eigen3/Eigen/Dense"
#include "myelement.h"
#include "material.h"

using namespace Eigen;

class TriangularElementSixNode :public myElement
{

private:
    int NDF;
    int NNE;

public:
    TriangularElementSixNode();

    //计算单元刚度矩阵
    MatrixXd calcEK(MatrixXd coords,Material material,double thickness);
};

#endif // TRIANGULARELEMENTSIXNODE_H
