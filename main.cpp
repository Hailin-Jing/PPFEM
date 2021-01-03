#include <Eigen3/Eigen/Dense>
#include <Src/mainwindow.h>
#include "test_gravityload.cpp"
#include "test_lineardistributedload.cpp"

#include <QApplication>
#include <iostream>
#include <model.h>
#include <QProcess>
#include "windows.h"
#include "shellapi.h"
using namespace Eigen;

int main(int argc, char *argv[])
{
//    test_gravityLoad(6);
    test_linearDistributedLoad(6);

    QApplication a(argc, argv);
    MainWindow w(nullptr,argc,argv);
    w.show();

    return a.exec();


    /*
//    int NDF = 2;
//    int NE = 1;
//    int NN = 6;
//    VectorXi IFIX;
//    IFIX.resize(NN*NDF);
//    IFIX<<1,0,1,0,0,0,0,0,0,0,0,0;
//    Matrix<int,Dynamic,Dynamic> EN;
//    EN.resize(NE,6);
//    EN<<1,2,3,4,5,6;
//    EN.array() -= 1;
//    Matrix<double,6,2> CXY;
//    CXY<<0,0,
//         1,0,
//         0,1,
//         0.5,0.5,
//         0,0.5,
//         0.5,0;

//    Material material = {"材料1",1,0,0};
//    TriangularElementSixNode element;
//    MatrixXd GK;
//    GK.resize(100,1);
//    GK.setZero();
//    for (int i = 0; i < 1; i++)
//    {
//        //(MatrixXi nodes, MatrixXd coords, MatrixXd& GK, int NN, int NE, MatrixXi EN, VectorXi IFIX,int SM)
//        Matrix<double,6,2> coords;
//        coords<<CXY(EN(i,0),0),CXY(EN(i,0),1),
//                CXY(EN(i,1),0),CXY(EN(i,1),1),
//                CXY(EN(i,2),0),CXY(EN(i,2),1),
//                CXY(EN(i,3),0),CXY(EN(i,3),1),
//                CXY(EN(i,4),0),CXY(EN(i,4),1),
//                CXY(EN(i,5),0),CXY(EN(i,5),1);

//        element.assembleToGlobal(EN.row(i),coords,GK,NN,NE,EN,IFIX,0);
//    }

//    Element element;
//    VectorXi AM = element.calcAM(NDF,NNE,NE,NN,IFIX,EN);

//    MatrixXd GK0,GK1,GK2;
//    GK0.resize(4,4);
//    GK0 << 1,2,0,0,
//          2,2,4,0,
//          0,4,3,4,
//          0,0,4,4;
//    VectorXd F;
//    F.resize(4);
//    F << 1,2,3,4;

//    GK2.resize(4,2);
//    GK2 << 1,2,2,4,3,4,4,0;

//    VectorXi AM,M;
//    GK1.resize(7,1);
//    GK1 << 1,2,2,3,4,4,4;
//    AM.resize(5);
//    AM <<1,2,4,6,8;
//    M.resize(4);
//    M << 1,1,2,3;

//    VectorXd X;
//    X = LU1(GK1,F,M,AM);*/
/*
    Model model;

    Material M("材料",1,0,7800);
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
*/
/*    Model model;

    Material M("材料",1,0,7800);
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
    IFIX(0) = 1; IFIX(2) = 1; IFIX(6) = 1; IFIX(7) = 1; IFIX(9) = 1; IFIX(11) = 1;
    model.setFixedDegree(IFIX);
    VectorXd F;
    F.resize(30);
    F.setZero();
    F(1) = -1;
    model.setLoad(F);

    VectorXd Delta = model.solveSystem(ET,SM,0,T);

    ShellExecuteW(nullptr,QString("open").toStdWString().c_str(),
                  QString("F:\\author.txt").toStdWString().c_str(),nullptr,nullptr,SW_SHOW);
*/
//    return 0;
}
