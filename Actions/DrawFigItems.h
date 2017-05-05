#ifndef _DRAW_FIG_ITM_
#define _DRAW_FIG_ITM_

#include "../ApplicationManager.h"
#include "Action.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

class DrawFigItems :public Action {

public:
	DrawFigItems(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

private:
	ActionType act;
};



#endif // !_DRAW_FIG_ITM_
