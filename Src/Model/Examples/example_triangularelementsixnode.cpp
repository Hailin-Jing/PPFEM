#include <iostream>
#include "Eigen3/Eigen/Dense"
#include "../Element/myelement.h"
#include "triangularelementthreenode.h"
#include "triangularelementsixnode.h"
#include "model.h"
using namespace Eigen;

/*int main()
{
    Model model;

    Material M = {"材料",1,0,7800};
    double T = 1;
    int ET = 6, SM = 1;
    model.addMaterial(M);

    MatrixXi EN;
    EN.resize(4,6);
    EN << 1,2,3,8,9,7,
          2,4,5,11,12,10,
          2,5,3,13,8,12,
          3,5,6,14,15,13;
    EN.array() -= 1;
    model.setElementNode(EN);
    MatrixXd CXY;
    CXY.resize(15,2);
    CXY << 0,2,
           0,1,
           1,1,
           0,0,
           1,0,
           2,0,
           0,1.5,
           0.5,1,
           0.5,1.5,
           0,0.5,
           0.5,0,
           0.5,0.5,
           1,0.5,
           1.5,0,
           1.5,0.5;
    model.setNodeCoordinate(CXY);
    VectorXi IFIX;
    IFIX.resize(30);
    IFIX.setZero();
    IFIX(0) = 1; IFIX(2) = 1; IFIX(6) = 1;
    IFIX(7) = 1; IFIX(9) = 1; IFIX(11) = 1;

    model.setFixedDegree(IFIX);
    VectorXd F;
    F.resize(30);
    F.setZero();
    F(1) = -1;
    model.setLoad(F);

    VectorXd Delta = model.solveSystem(ET,SM,0,T);
    std::cout<<"closed\n";
    return 0;
}*/
