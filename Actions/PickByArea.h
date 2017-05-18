#ifndef _PICK_AREA_
#define _PICK_AREA_

#include "Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../CMUgraphicsLib/colors.h"
#include <algorithm>

class PickByArea : public Action {
public:
	PickByArea(ApplicationManager *app_p);
    ~PickByArea();

    virtual void ReadActionParameters();
	virtual void Execute(bool redo = false);
	virtual void Undo();
	
private:
	void DeleteCorrect(int id);
	deque<CFigure*> figures;
};

#endif