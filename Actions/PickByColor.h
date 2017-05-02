#ifndef _PICK_COLOR_
#define _PICK_COLOR_

#include "Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

class PickByColor :public Action {

public:
	PickByColor(ApplicationManager *app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();


};


#endif // !_PICK_COLOR_
