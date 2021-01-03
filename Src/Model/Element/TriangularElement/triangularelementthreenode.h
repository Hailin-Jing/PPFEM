#ifndef TRIANGULARELEMENTTHREENODE_H
#define TRIANGULARELEMENTTHREENODE_H

#include "Eigen3/Eigen/Dense"
#include "myelement.h"
#include "material.h"

using namespace Eigen;

class TriangularElementThreeNode : public myElement
{

private:
    int NDF;
    int NNE;

public:
    TriangularElementThreeNode();

    //计算单元刚度矩阵
    MatrixXd calcEK(MatrixXd coords,Material material,double thickness);
};

#endif // TRIANGULARELEMENTTHREENODE_H
