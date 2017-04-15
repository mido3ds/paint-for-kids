#ifndef __CH_FILL_COLOR__
#define __CH_FILL_COLOR__

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"
#include "../CMUgraphicsLib/colors.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ChFillColor : public Action {
public:
	ChFillColor(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual ActionType GetActType() { return CHNG_FILL_CLR; }

private:
	color C = UI.FillColor,
		lastC = C;
};

#endif // !_CH_FILL_COLOR_
