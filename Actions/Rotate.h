#ifndef _ROTATE_
#define _ROTATE_

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"

class Rotate : public Action {
public:
	Rotate(ApplicationManager* app_p);

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();

	virtual ActionType GetActType() { return ROTATE; }

private:
	int deg;
};

#endif // !_ROTATE_
