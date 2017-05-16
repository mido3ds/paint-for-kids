#ifndef _PICK_TYPE_AND_COLOR_
#define _PICK_TYPE_AND_COLOR_

#include "Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../CMUgraphicsLib/colors.h"

class PickByTypeAndColor : public Action {
public:
	PickByTypeAndColor(ApplicationManager *app_p);
	~PickByTypeAndColor();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();

private:
	deque<CFigure *> figures;
	color c;
	string type;
	bool isfilled;
	int correct = 0;
	int wrong = 0;
	int GetNumFigsSameTypeAndColor(color C, bool isfilled,string type);

	void DeleteCorrect(int id);

	void DrawColorCircle(color c);

	bool Correct(CFigure *fig);
	void PrintPickInfo(string, color, int, int);
	
};

#endif