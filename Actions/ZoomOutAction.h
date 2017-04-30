#ifndef __ZoomOutAction_h__
#define __ZoomOutAction_h__

#include "Action.h"
#include "../ApplicationManager.h"

#include "../Figures/CCircle.h"
#include "../Figures/CRectangle.h"
#include "../Figures/CTrngl.h"
#include "../Figures/CLine.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"


//Add ZoomOut Action class
class ZoomOutAction : public Action
{
public:
	ZoomOutAction(ApplicationManager* app_p);

	virtual void ReadActionParameters();
	virtual void Execute();

	void SetZoompoint(Point z_point);

	Point GetZoomPoint() const;

	virtual void Undo();

private:
	Point zoom_point;
};

#endif  /* __ZoomOutAction_h__ */