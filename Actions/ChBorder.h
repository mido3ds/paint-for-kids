#ifndef _CH_BORDER_
#define _CH_BORDER_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"
#include "../CMUgraphicsLib/colors.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ChBorder : public Action {
public:
	ChBorder(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual ActionType GetActType() { return CHNG_DRAW_CLR; }

private:
	color C = UI.DrawColor,
		lastC = C;
	int w = UI.PenWidth,
		lastW = w;

};

#endif // !_CH_BORDER_
