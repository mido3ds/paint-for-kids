#ifndef _PICK_
#define _PICK_

#include "../ApplicationManager.h"
#include "Action.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

class PickAction : public Action {
public:
	PickAction(ApplicationManager* app_p);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();

private:
	ActionType act;
};

#endif // !_PICK_
