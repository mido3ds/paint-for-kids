#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures/Figure.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include <vector>

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
    void AddFigure(Figure* fig_p); //Adds a new figure to the fig_list
    Figure* GetFigure(int x, int y) const; //Search for a figure given a point inside the figure

    // -- Interface Management Functions
    Input* GetInput() const; //Return pointer to the input
    Output* GetOutput() const; //Return pointer to the output
    void UpdateInterface() const; //Redraws all the drawing window

private:
    vector<Figure*> fig_list;

    //Pointers to Input and Output classes
    Input* in_p;
    Output* out_p;
};

#endif