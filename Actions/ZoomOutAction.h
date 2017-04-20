#ifndef __ZoomOutAction_h__
#define __ZoomOutAction_h__

#include "../ApplicationManager.h"
#include "Action.h"

#include "../Figures/CCircle.h"
#include "../Figures/CLine.h"
#include "../Figures/CRectangle.h"
#include "../Figures/CTrngl.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

//Add ZoomOut Action class
class ZoomOutAction : public Action {
public:
    ZoomOutAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    void SetZoomFactor(double z_factor);
    void SetZoompoint(Point z_point);

    double GetZoomFactor() const;
    Point GetZoomPoint() const;

    virtual void Undo();

    virtual ActionType GetActType() { return ZOOM_OUT; }

private:
    double zoom_factor;
    Point zoom_point;
};

#endif /* __ZoomOutAction_h__ */