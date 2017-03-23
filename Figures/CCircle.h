#ifndef __CCircle_h__
#define __CCircle_h__

#include "CFigure.h"

class CCircle : public CFigure
{
public:
    CCircle();
    CCircle(Point p1, Point p2, GfxInfo circ_gfx_info);

    virtual void Draw(Output* out_p) const;

    Point p1, p2;
};

#endif  /* __CCircle_h__ */