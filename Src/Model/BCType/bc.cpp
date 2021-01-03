#include "bc.h"

BC::BC(int BCIndex,int PRIndex,double MinRange,double MaxRange,bool DCX,bool DCY)
{
    this->BCIndex = BCIndex;
    this->PRIndex = PRIndex;
    this->MinRange = MinRange;
    this->MaxRange = MaxRange;
    this->DegreeConstraintX = DCX;
    this->DegreeConstraintY = DCY;
}
