#ifndef _DOWN_
#define _DOWN_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class Down : public Action {
public:
	Down(ApplicationManager* app_p);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual ActionType GetActType() { return SEND_BACK; }

private:
};

#endif // !_DOWN_
