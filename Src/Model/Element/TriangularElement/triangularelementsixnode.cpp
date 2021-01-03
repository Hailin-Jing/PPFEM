#include "triangularelementsixnode.h"

TriangularElementSixNode::TriangularElementSixNode()
{
    NDF = 2;
    NNE = 6;
}

MatrixXd TriangularElementSixNode::calcEK(MatrixXd coords,Material material,double thickness)
{
    MatrixXd EK;
    EK.resize(12,12);
    EK.setZero();

    //弹性矩阵
    Matrix<double,3,3> D;
    double E = material.E;
    double ANU = material.ANU;
    D<< 1,  ANU,      0,
       ANU,  1,       0,
       0,    0,   (1-ANU)/2;
    D = D * E / (1-ANU*ANU);

    Matrix<double,3,3> DD;
    DD<<1,coords(0,0),coords(0,1),
        1,coords(1,0),coords(1,1),
        1,coords(2,0),coords(2,1);

    //三角形面积的两倍
    double S2 = DD.determinant();

    //应变矩阵
    std::vector<double> b,c;
    b.resize(3);
    c.resize(3);
    for (unsigned int i = 0; i < 3; i++)
    {
        b[i] = coords((i+1) % 3,1) - coords((i+2) % 3,1);
        c[i] = - coords((i+1) % 3,0) + coords((i+2) % 3,0);
    }

    Matrix<double,2,2> F,G,P,Q;
    for (unsigned int i = 0; i < 3; i++)
    {
        F << 6*b[i]*b[i]+3*(1-ANU)*c[i]*c[i], 3*(1+ANU)*b[i]*c[i],
             3*(1+ANU)*b[i]*c[i], 6*c[i]*c[i]+3*(1-ANU)*b[i]*b[i];
        EK.block(2*i,2*i,2,2) = F;
    }
    for (unsigned int i = 0; i < 3; i++)
    {
        G << 16*(b[i]*b[i]-b[(i+1) % 3]*b[(i+2) % 3]) + 8*(1-ANU)*(c[i]*c[i]-c[(i+1) % 3]*c[(i+2) % 3]),
             4*(1+ANU)*(b[i]*c[i] + b[(i+1) % 3]*c[(i+1) % 3] + b[(i+2) % 3]*c[(i+2) % 3]),
             4*(1+ANU)*(b[i]*c[i] + b[(i+1) % 3]*c[(i+1) % 3] + b[(i+2) % 3]*c[(i+2) % 3]),
             16*(c[i]*c[i]-c[(i+1) % 3]*c[(i+2) % 3]) + 8*(1-ANU)*(b[i]*b[i]-b[(i+1) % 3]*b[(i+2) % 3]);
        EK.block(2*i+6,2*i+6,2,2) = G;
    }
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (j == i)
                continue;
            P << -2*b[i]*b[j]-(1-ANU)*c[i]*c[j],
                 -2*ANU*b[i]*b[j]-(1-ANU)*c[i]*b[j],
                 -2*ANU*b[i]*b[j]-(1-ANU)*b[i]*c[j],
                 -2*c[i]*c[j]-(1-ANU)*b[i]*b[j];
            EK.block(2*i,2*j,2,2) = P;
//            std::cout<<"(2*j+2)%6+6="<<(2*j+2)%6+6<<"  2*i+6="<<2*i+6<<endl;
            if ((2*j+2)%6+6 == 2*i+6)
            {
//                std::cout<<"(2*j+4)%6+6="<<(2*j+4)%6+6<<endl;
                EK.block(2*i,(2*j+4)%6+6,2,2) = -4*P;
                EK.block((2*j+4)%6+6,2*i,2,2) = -4*P;
            }
            else
            {
                EK.block(2*i,(2*j+2)%6+6,2,2) = -4*P;
                EK.block((2*j+2)%6+6,2*i,2,2) = -4*P;
            }
        }
    }
    for (unsigned i = 0; i < 3; i++)
    {
        for (unsigned j = 0; j < 3; j++)
        {
            if (j == i)
                continue;
            Q << 16*b[i]*b[j]+8*(1-ANU)*c[i]*c[j],
                 4*(1+ANU)*(c[i]*b[j]+b[i]*c[j]),
                 4*(1+ANU)*(c[i]*b[j]+b[i]*c[j]),
                 16*c[i]*c[j]+8*(1-ANU)*b[i]*b[j];
            EK.block(2*i+6,2*j+6,2,2) = Q;
        }
    }
    EK = EK * E * thickness / (24 * (1 - ANU * ANU) * S2 / 2);
    return EK;
}
