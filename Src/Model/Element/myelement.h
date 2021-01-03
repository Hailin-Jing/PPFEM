#ifndef MYELEMENT_H
#define MYELEMENT_H

#include "Eigen3/Eigen/Dense"
#include <iostream>
#include <vector>
#include <QString>
#include "material.h"
using namespace Eigen;

class myElement
{

public:
    myElement();
    virtual ~myElement();

    //计算单元刚度矩阵
    virtual MatrixXd calcEK(MatrixXd,Material,double){return MatrixXd();}

};



#endif // ELEMENT_H
