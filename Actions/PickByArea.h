#ifndef _PICK_AREA_
#define _PICK_AREA_\

#include "Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../CMUgraphicsLib/colors.h"
#include <algorithm>
class PickByArea :
	public Action
{
public:
	PickByArea(ApplicationManager *app_p);
	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();
	~PickByArea();
private:
	
	deque<CFigure *> figures;
	void DeleteCorrect(int id);
};

#endif