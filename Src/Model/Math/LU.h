#ifndef LU_H
#define LU_H

#include "Eigen3/Eigen/Dense"
#include "qmath.h"
using namespace Eigen;

VectorXd LU0(MatrixXd GK,VectorXd F)
{
    VectorXd Delta;
    MatrixXd S;
    VectorXd V;
    Delta.resize(F.size());
    S.resize(GK.rows(),GK.cols());
    V.resize(F.size());
    S.setZero(); V.setZero();
    int Rows = int(GK.rows());

    //消元
    for (int i = 0; i < Rows; i++)
    {
        for (int j = i; j < Rows; j++)
        {
            S(i,j) = GK(i,j);
            for (int m = 0; m <= i - 1; m++)
                S(i,j) -= S(m,i) * S(m,j) / S(m,m);
        }
        V(i) = F(i);
        for (int m = 0; m <= i - 1; m++)
            V(i) -= S(m,i) * V(m) / S(m,m);
    }
    //回代
    Delta(Rows-1) = V(Rows-1) / S(Rows-1,Rows-1);
    for (int i = Rows - 2; i >= 0; i--)
    {
        Delta(i) = V(i);
        for (int j = i + 1; j < Rows; j++)
            Delta(i) -= S(i,j) * Delta(j);
        Delta(i) /= S(i,i);
    }
    return Delta;
}

VectorXd LU1(MatrixXd GK,VectorXd F,VectorXi M,VectorXi AM)
{
    VectorXd Delta;
    VectorXd S,V;
    Delta.resize(F.size());
    S.resize(GK.size()); V.resize(F.size());
    S.setZero(); V.setZero();
    int Rows = int(F.size());
    int m0, k, Mi, Mj;

    //消元
    for (int j = 0; j < Rows; j++)
    {
        for (int i = M(j) - 1; i <= j; i++)
        {
            m0 = qMax(M(i),M(j)) - 1;
            k = (AM(j) - 1) + j - i;
            S(k) = GK(k);
            for (int m = m0; m <= i - 1; m++)
            {
                Mi = (AM(i) - 1) + i - m;
                Mj = (AM(j) - 1) + j - m;
                S(k) -= S(Mi) * S(Mj) / S(AM(m)-1);
            }
        }
        V(j) = F(j);
        for (int m = M(j) - 1; m <= j - 1; m++)
        {
            Mj = (AM(j) - 1) + j - m;
            V(j) -= S(Mj) * V(m) / S(AM(m)-1);
        }
    }
    //回代
    Delta(Rows-1) = V(Rows-1) / S(AM(Rows-1)-1);
    for (int i = Rows - 2; i >= 0; i--)
    {
        Delta(i) = V(i);
        for (int j = i + 1; j < Rows; j++)
            if (M(j) - 1 <= i)
            {
                k = (AM(j) - 1) + j - i;
                Delta(i) -= S(k) * Delta(j);
            }
        Delta(i) /= S(AM(i) - 1);
    }
    return Delta;
}

VectorXd LU2(MatrixXd GK,VectorXd F)
{
    VectorXd Delta;
    MatrixXd S;
    VectorXd V;
    Delta.resize(F.size());
    S.resize(GK.rows(),GK.cols());
    V.resize(F.size());
    S.setZero(); V.setZero();
    int Rows = int(GK.rows());
    int Cols = int(GK.cols());
    int m0;

    //消元
    for (int i = 0; i < Rows; i++)
    {
        for (int j = i; j < qMin(i + Cols, Rows); j++)
        {
            m0 = qMax(j - Cols + 1, 0);
            S(i,j-i) = GK(i,j-i);
            for (int m = m0; m < i; m++)
                S(i,j-i) -= S(m,i-m) * S(m,j-m) / S(m,0);
        }
        m0 = qMax(i - Cols + 1, 0);
        V(i) = F(i);
        for (int m = m0; m < i; m++)
            V(i) -= S(m,i-m) * V(m) / S(m,0);
    }
    //回代
    Delta(Rows-1) = V(Rows-1) / S(Rows-1,0);
    for (int i = Rows - 2; i >= 0; i--)
    {
        m0 = qMin(i + Cols, Rows);
        Delta(i) = V(i);
        for (int j = i + 1; j < m0; j++)
            Delta(i) -= S(i,j-i) * Delta(j);
        Delta(i) /= S(i,0);
    }
    return Delta;
}

#endif // LU_H
