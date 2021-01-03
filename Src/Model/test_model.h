#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Eigen3/Eigen/Dense"
using namespace Eigen;
#include "model.h"

void test_model(int ET,MatrixXd &CXY,MatrixXi &EN)
{
    switch(ET)
    {
    case 3:
    {
        CXY.resize(6,2);
        EN.resize(4,3);
        CXY << 0,1,
               1,1,
               2,1,
               0,0,
               1,0,
               2,0;
        EN << 1,4,2,
              4,5,2,
              5,6,2,
              6,3,2;
        break;
    }
    case 6:
    {
        CXY.resize(15,2);
        EN.resize(4,6);
        CXY << 0,1,
               1,1,
               2,1,
               0,0,
               1,0,
               2,0,
               0,0.5,
               0.5,1,
               0.5,0.5,
               0.5,0,
               1,0.5,
               1.5,1,
               1.5,0.5,
               1.5,0,
               2,0.5;
        EN << 1,4,2,9,8,7,
              4,5,2,11,9,10,
              5,6,2,13,11,14,
              6,3,2,12,13,15;
        break;
    }
    }
    EN.array() -= 1;
}
#endif // TEST_MODEL_H
