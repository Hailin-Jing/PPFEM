#ifndef DXFFILTER_H
#define DXFFILTER_H

#include "dxflib/src/dl_creationinterface.h"
#include "dxflib/src/dl_creationadapter.h"
#include "dxflib/src/dl_attributes.h"
#include "dxflib/src/dl_codes.h"
#include "dxflib/src/dl_entities.h"
#include "dxflib/src/dl_exception.h"
#include "dxflib/src/dl_global.h"
#include "dxflib/src/dl_writer.h"
#include "dxflib/src/dl_writer_ascii.h"

#include <vector>
#include <iostream>
#include <limits>
#include <QRectF>
#include "primitive.h"

class DXFFilter : public DL_CreationAdapter
{
private:
    std::vector<Primitive> primitives;
    int primitiveNmuber = 0;
    double minX = INT_MAX;
    double minY = INT_MAX;
    double maxX = INT_MIN;
    double maxY = INT_MIN;

public:
    DXFFilter();

    //添加线元
    virtual void addLine(const DL_LineData&);
    virtual void addArc(const DL_ArcData&);
    virtual void addCircle(const DL_CircleData&);

    //获取线元
    int getPrimitiveNmuber();
    std::vector<Primitive> getPrimitives();

    //辅助函数
    //获取闭合图形索引，第一个索引为图形数，第二个索引为图元，第三个索引为正序或倒序
    std::vector<std::vector<std::vector<int>>> getCPI(int);
        int *copy(int*,int);
        int directionPolygen(std::vector<std::vector<double>>);
        std::vector<std::vector<int>> reverse(std::vector<std::vector<int>>);

    //获取图形范围
    std::vector<double> getRange();

};

#endif // DXFFILTER_H
