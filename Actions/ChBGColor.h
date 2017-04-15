#ifndef _CH_BG_COLOR_
#define _CH_BG_COLOR_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"
#include "../CMUgraphicsLib/colors.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ChBGColor : public Action {
public:
	ChBGColor(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual ActionType GetActType() { return CHNG_BK_CLR; }

private:
	color C = UI.BkGrndColor;
	color lastC = C;
};

#endif // !_CH_BG_COLOR_
