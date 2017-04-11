#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure {
public:
    CRectangle();
    CRectangle(Point, Point, GfxInfo figure_gfx_info);

    virtual void Draw(Output* out_p) const;

    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);

    Point p1, p2;
};

#endif