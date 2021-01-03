#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>

class Material
{
public:
    QString MN;             //材料名
    double E;               //弹性模量
    double ANU;             //泊松比
    double Density;         //密度
    Material(QString MN,double E,double ANU,double Density)
    {
        this->MN = MN;
        this->E = E;
        this->ANU = ANU;
        this->Density = Density;
    }
};

#endif // MATERIAL_H
