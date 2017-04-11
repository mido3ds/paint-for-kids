#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include <set>
#include <string>

// actions files
#include "Actions/AddCircAction.h"
#include "Actions/AddLineAction.h"
#include "Actions/AddRectAction.h"
#include "Actions/AddTrnglAction.h"
#include "Actions/ExitAction.h"
#include "Actions/LoadAction.h"
#include "Actions/SaveAction.h"
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

private:
    // TODO: set vs multiset,chooe the best
    multiset<CFigure*, CmpFigures> figs;

    //Pointers to Input and Output classes
    Input* in_p;
    Output* out_p;
};

#endif