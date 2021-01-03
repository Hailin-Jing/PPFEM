#ifndef BC_H
#define BC_H

struct BC
{
    int BCIndex;
    int PRIndex;
    double MinRange;
    double MaxRange;
    bool DegreeConstraintX;
    bool DegreeConstraintY;

    BC(int BCIndex,int PRIndex,double MinRange,double MaxRange,bool DCX,bool DCY);
};

#endif // BC_H
