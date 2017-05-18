#ifndef _PICK_COLOR_
#define _PICK_COLOR_

#include "Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../CMUgraphicsLib/colors.h"

class PickByColor : public Action {

public:
	PickByColor(ApplicationManager *app_p);
    ~PickByColor();

    virtual void ReadActionParameters();
	virtual void Execute(bool redo = false);
	virtual void Undo();

private:
	deque<CFigure *> figures;
	color c;
	bool isfilled;

	int GetNumFigsSameColor(color C, bool isfilled);

	void DeleteCorrect(int id);

	void DrawColorCircle(color c);

	bool correct(CFigure *fig);
};


#endif // !_PICK_COLOR_