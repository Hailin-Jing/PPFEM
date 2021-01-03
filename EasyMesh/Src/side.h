/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef SIDE_H
#define SIDE_H
#include "precision.h"
#include <vector>

////////////
//        //
//  Side  //
//        //
////////////
class Side
{
public:
    Side(const int n) : stride(8192)
    {
        sd.resize( n ); pos=0;
    }
    Side()            : stride(8192) 
    {
        pos = 0;
        ea = eb = 0;
        a = b = c = d = 0;
        mark = 0;
        s = 0.0;
        new_numb = 0;
    }

    int size()
    {
        return int(pos);
    }
    void increase_size(const int inc)
    {
        pos += unsigned(inc);
        if(pos>=sd.size()) sd.resize(sd.size() + unsigned(stride));
    }

    int ea, eb;           /* left and right element */
    int a, b, c, d;       /* left, right, start and end point */
    int mark;             /* is it off, is on the boundary */
    real s;
    int new_numb;         /* used for renumeration */

    std::vector<Side> sd;
    Side & operator [] (const int i)
    {
        return sd.at(unsigned(i));
    }

private:
    unsigned pos;
    int      stride;
};

#endif
