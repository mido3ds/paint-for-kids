#ifndef _DRAW_FIG_ACT_
#define _DRAW_FIG_ACT_

#include "../ApplicationManager.h"
#include "Action.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

class DrawFigActions :public Action {

public:
	DrawFigActions(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

private:
	ActionType act;
};


#endif // !_DRAW_FIG_ACT_
