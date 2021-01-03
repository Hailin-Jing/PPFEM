/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "precision.h"

///////////////
//           //
//  Element  //
//           //
///////////////

class Element
{
public:
    Element(const int n) : stride(4096)
    {
        el.resize(unsigned(n));pos=0;
    }
    Element()            : stride(4096) 
    {
        pos = 0;
        i = j= k=0;
        ei=ej=ek=0;
        si=sj=sk=0;
        mark     = 0;
        state    = 0;
        material = 0;
        xv = yv = xin = yin = R = r = Det = 0.0;
        new_numb = 0;
    }

    int size()
    {
        return int(pos);
    }
    void increase_size(const int inc)
    {
      pos += unsigned(inc);
      if(pos>=el.size()) el.resize(el.size()+unsigned(stride));
    }

    int i,  j,  k;
    int ei, ej, ek;
    int si, sj, sk;
    int mark;             /* is it off (ON or OFF) */
    int state;            /* is it (D)one, (A)ctive or (W)aiting */
    int material;
    real xv, yv, xin, yin, R, r, Det;
    int new_numb;         /* used for renumeration */

    std::vector<Element> el;
    Element & operator [] (const int i)
    {
        return el.at(unsigned(i));
    }

private:
    unsigned pos;
    int      stride;
 };

#endif
