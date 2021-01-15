#ifndef FEMELEMENT_H
#define FEMELEMENT_H

#include "Eigen3/Eigen/Dense"
#include <iostream>
#include <vector>
#include <QString>
#include "material.h"
using namespace Eigen;

class FEMElement
{

public:
    FEMElement();
    virtual ~FEMElement();

    //计算单元刚度矩阵
    virtual MatrixXd calcEK(MatrixXd,Material,double){return MatrixXd();}

};



#endif // FEMElement
