#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include <set>
#include <string>
#include <stack>

// actions files
#include "Actions/AddCircAction.h"
#include "Actions/AddLineAction.h"
#include "Actions/AddRectAction.h"
#include "Actions/AddTrnglAction.h"
#include "Actions/ExitAction.h"
#include "Actions/LoadAction.h"
#include "Actions/SaveAction.h"
#include "Actions/UndoAction.h"
#include "Actions/RedoAction.h"
#include "Actions/SwitchDrawMode.h"
#include "Actions/SwitchPlayMode.h"

// figures files
#include "Figures/CCircle.h"
#include "Figures/CFigure.h"
#include "Figures/CLine.h"
#include "Figures/CRectangle.h"
#include "Figures/CTrngl.h"

//Main class that manages everything in the application.
class ApplicationManager {
public:
    ApplicationManager();
    ~ApplicationManager();

    // -- Action-Related Functions
    //Reads the input command from the user and returns the corresponding action type
    ActionType GetUserAction() const;
    void ExecuteAction(ActionType); //Creates an action and executes it

    // -- Figures Management Functions
    void AddFigure(CFigure* fig_p); //Adds a new figure to the figs
    CFigure* GetFigure(int x, int y) const; //Search for a figure given a point inside the figure

    // -- Interface Management Functions
    Input* GetInput() const; //Return pointer to the input
    Output* GetOutput() const; //Return pointer to the output
    void UpdateInterface() const; //Redraws all the drawing window

    void SaveAll(ofstream& out_file);
    void LoadAll(ifstream& in_file);

    Action* DetectAction(ActionType act_type);
    CFigure* DetectFigure(string fig_name);

    // pop last action from undo_dt, undo it, push it to redo_st
    void Undo();
    // pop last action from redo_st, redo it, push it to undo_st
    void Redo();

private:
    multiset<CFigure*, CmpFigures> figs;

    // for undo and redo
    stack<Action*> undo_st;
    stack<Action*> redo_st;

    //Pointers to Input and Output classes
    Input* in_p;
    Output* out_p;
};

#endif