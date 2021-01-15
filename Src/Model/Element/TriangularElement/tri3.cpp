#include "tri3.h"

TRI3::TRI3()
{
    NDF = 2;
    NNE = 3;
}

MatrixXd TRI3::calcEK(MatrixXd coords,Material material,double thickness)
{
    MatrixXd EK;
    EK.resize(6,6);
    EK.setZero();

    //弹性矩阵
    Matrix<double,3,3> D;
    double E = material.E;
    double ANU = material.ANU;
    D<<  1,  ANU,           0,
       ANU,    1,           0,
         0,    0,   (1-ANU)/2;
    D = D * E / (1-ANU*ANU);

    Matrix<double, 3, 3> DD;
    DD << 1, coords(0,0), coords(0,1),
          1, coords(1,0), coords(1,1),
          1, coords(2,0), coords(2,1);

    //三角形面积的两倍
    double S2 = DD.determinant();

    //应变矩阵
    double bi = coords(1,1) - coords(2,1);
    double bj = coords(2,1) - coords(0,1);
    double bm = coords(0,1) - coords(1,1);

    double ci = - coords(1,0) + coords(2,0);
    double cj = - coords(2,0) + coords(0,0);
    double cm = - coords(0,0) + coords(1,0);

    Matrix<double, 3, 2> Bi,Bj,Bm;
    Matrix<double, 3, 6> B;

    Bi << bi, 0, 0, ci, ci, bi;
    Bj << bj, 0, 0, cj, cj, bj;
    Bm << bm, 0, 0, cm, cm, bm;

    B << Bi, Bj, Bm;

    //单元刚度矩阵
    EK = B.transpose() * D * B * thickness * S2 / 2;
    return EK;
}
