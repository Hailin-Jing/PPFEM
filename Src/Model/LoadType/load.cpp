#include "load.h"

LOAD::LOAD
(int LoadIndex, int LoadType, int PRIndex, double MinRange, double MaxRange,
           double BPX, double BPY, double EPX, double EPY)
{
    this->LoadIndex = LoadIndex;
    this->LoadType = LoadType;
    this->PRIndex = PRIndex;
    this->MinRange = MinRange;
    this->MaxRange = MaxRange;
    this->BPX = BPX;
    this->BPY = BPY;
    this->EPX = EPX;
    this->EPY = EPY;
}
