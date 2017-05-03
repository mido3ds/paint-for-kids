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
    void UpdateMessage(int invalid, int valid); // make mesage and prints it with needed info
    CFigure* ChooseRandomFigure(); // random figure from left
    CFigure* GetFigureFromRight(Point p); // given a point, get its figure from left_figs

private:
    deque<CFigure*> right_figs; // figures in the left
    deque<CFigure*> left_figs; // figures in the right

    Output* out_p = nullptr;
    Input* in_p = nullptr;

    CLine middle_line;
};

#endif