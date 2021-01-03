#ifndef LOAD_H
#define LOAD_H

struct LOAD
{
    int LoadIndex;
    int LoadType;
    int PRIndex;
    double MinRange;
    double MaxRange;
    double BPX;
    double BPY;
    double EPX;
    double EPY;

    LOAD(int LoadIndex,int LoadType,int PRIndex,double MinRange,
         double MaxRange,double BPX,double BPY,double EPX,double EPY);
};

#endif // LOAD_H
