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

    void UpdateInterface(); // redraws the figures
    void ShuffleFigures(); // randomized r_figs positions
    deque<CFigure*>::iterator RandomFigure(); // get iterator to random figure from left

private:
    deque<CFigure*> l_figs; // figures in the left
    deque<CFigure*> r_figs; // figures in the right

    Output* out_p = nullptr;
    Input* in_p = nullptr;

    CLine middle_line;
};

#endif