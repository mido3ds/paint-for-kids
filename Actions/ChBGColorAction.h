#ifndef _CH_BG_COLOR_
#define _CH_BG_COLOR_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"
#include "../CMUgraphicsLib/colors.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ChBGColorAction : public Action {
public:
	ChBGColorAction(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	

private:
	color C = UI.BkGrndColor;
	color lastC = C;
};

#endif // !_CH_BG_COLOR_
