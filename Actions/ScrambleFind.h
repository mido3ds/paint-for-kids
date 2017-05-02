#ifndef __ScrambleFind_H__
#define __ScrambleFind_H__

#include "../ApplicationManager.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ScrambleFind : public Action {
public:
    ScrambleFind(ApplicationManager* app_p);
	~ScrambleFind();

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

private:
    deque<CFigure*> l_figs; // figures in the left
    deque<CFigure*> r_figs; // figures in the right
};

#endif