#ifndef __ZoomInAction_h__
#define __ZoomInAction_h__

#include "Action.h"
#include "../ApplicationManager.h"

#include "../Figures/CCircle.h"
#include "../Figures/CRectangle.h"
#include "../Figures/CTrngl.h"
#include "../Figures/CLine.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"


//Add ZoomIn Action class
class ZoomInAction : public Action
{
public:
	ZoomInAction(ApplicationManager* app_p);

	void SetZoompoint(Point z_point);
	Point GetZoomPoint() const;

	virtual void ReadActionParameters();
	virtual void Execute(bool redo = false);
	virtual void Undo();
	
private:
	Point zoom_point;
	Point pre_zoom_point;
};
#endif  /* __ZoomInAction_h__ */