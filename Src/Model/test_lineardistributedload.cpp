#include "Eigen3/Eigen/Dense"
using namespace Eigen;
#include "model.h"
#include "test_model.h"
#include <iostream>

void test_linearDistributedLoad(int ET)
{
    Model model;
    MatrixXd CXY;
    MatrixXi EN;
    VectorXd Load;
    test_model(ET,CXY,EN);
    Load.resize(CXY.rows()*2);
    Load.setZero();
    MatrixXd DL;
    DL.resize(1,13);
    DL << 0,
          1,1,2,2,
          0,0,0,0,
          0,0,0,0;
//    model.calcLinearDistributedLoad(ET,CXY,EN,Load,DL,1);
    std::cout<<"successfully"<<std::endl;
}
