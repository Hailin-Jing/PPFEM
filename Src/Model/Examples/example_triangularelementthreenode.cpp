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
    int ET = 3, SM = 2;
    model.addMaterial(M);

    MatrixXi EN;
    EN.resize(4,3);
    EN << 1,2,3,
          2,4,5,
          2,5,3,
          3,5,6;
    EN.array() -= 1;
    model.setElementNode(EN);
    MatrixXd CXY;
    CXY.resize(6,2);
    CXY << 0,2,
           0,1,
           1,1,
           0,0,
           1,0,
           2,0;
    model.setNodeCoordinate(CXY);
    VectorXi IFIX;
    IFIX.resize(12);
    IFIX << 1,0,1,0,0,0,1,1,0,1,0,1;
    model.setFixedDegree(IFIX);
    VectorXd F;
    F.resize(12);
    F << 0,-1,0,0,0,0,0,0,0,0,0,0;
    model.setLoad(F);

    VectorXd Delta = model.solveSystem(ET,SM,0,T);
    std::cout<<"closed\n";
    return 0;
}*/
