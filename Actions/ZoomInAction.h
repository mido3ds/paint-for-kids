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

	void SetZoomFactor(double z_factor);
	void SetZoompoint(Point z_point);

	double GetZoomFactor() const;
	Point GetZoomPoint() const;

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	
	virtual ActionType GetActType() { return ZOOM_IN; }

private:
	double zoom_factor;
	Point zoom_point;
};


#endif  /* __ZoomInAction_h__ */