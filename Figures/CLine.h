#ifndef __CLine_h__
#define __CLine_h__

#include "CFigure.h"

class CLine : public CFigure {
public:
    CLine();
    CLine(Point p1, Point p2, GfxInfo line_gfx_info);

    virtual void Draw(Output* out_p) const;

    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);

    Point p1, p2;
};

#endif /* __CLine_h__ */