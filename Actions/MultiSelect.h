#ifndef _MULTI_SELECT_
#define _MULTI_SELECT_

#include "../ApplicationManager.h"
#include "Action.h"

class MultiSelect : public Action {
public:
	MultiSelect(ApplicationManager *app_p);

	virtual void ReadActionParameters();
	virtual void Execute(bool redo = false);
	virtual void Undo();
};

#endif // !_MULTI_SELECT_