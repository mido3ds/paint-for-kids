#ifndef _DOWN_
#define _DOWN_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class DownAction : public Action {
public:
	DownAction(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	

private:
};

#endif // !_DOWN_
