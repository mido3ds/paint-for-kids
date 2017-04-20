#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include <fstream>
#include <set>
#include <stack>
#include <string>
#include <vector>

// actions files
#include "Actions/AddCircAction.h"
#include "Actions/AddLineAction.h"
#include "Actions/AddRectAction.h"
#include "Actions/AddTrnglAction.h"
#include "Actions/ChBGColorAction.h"
#include "Actions/ChBorderAction.h"
#include "Actions/ChFillColorAction.h"
#include "Actions/CopyAction.h"
#include "Actions/CutAction.h"
#include "Actions/DeleteAction.h"
#include "Actions/DownAction.h"
#include "Actions/ExitAction.h"
#include "Actions/LoadAction.h"
#include "Actions/MoveAction.h"
#include "Actions/PasteAction.h"
#include "Actions/RedoAction.h"
#include "Actions/ResizeAction.h"
#include "Actions/RotateAction.h"
#include "Actions/SaveAction.h"
#include "Actions/SelectAction.h"
#include "Actions/ToDrawModeAction.h"
#include "Actions/ToPlayModeAction.h"
#include "Actions/UnSelectAction.h"
#include "Actions/UndoAction.h"
#include "Actions/UpAction.h"
#include "Actions/ZoomInAction.h"
#include "Actions/ZoomOutAction.h"

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
    void ExecuteAction(Action* action); //Takes already created action and excute it

    // -- Figures Management Functions
    void AddFigure(CFigure* fig_p); //Adds a new figure to the figs
    CFigure* GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
    multiset<CFigure*, CmpFigures>* GetFigures(); //Search for a figure given it's index in figure list

    // -- Interface Management Functions
    Input* GetInput() const; //Return pointer to the input
    Output* GetOutput() const; //Return pointer to the output
    int GetZoom() const; //Return value of zoom
    Point GetManagerZoomPoint() const; //Return current zooming if there was zooming
    void UpdateInterface(); //Redraws all the drawing window

    void SaveAll(ofstream& out_file);
    void LoadAll(ifstream& in_file);

    Action* DetectAction(ActionType act_type);
    CFigure* DetectFigure(string fig_name);

    // pop last action from undo_dt, undo it, push it to redo_st
    void Undo();
    // pop last action from redo_st, redo it, push it to undo_st
    void Redo();

    // returns the next available id to assign to the fig
    // used by Action to make the figure
    unsigned int GenerateNextId();

    // used by Action::Undo to delete a made-before figure given the stored id of it
    void DeleteFigure(unsigned int id);

    bool ChangeSelectedFillColor(color c);

    bool ChangeSelectedBorder(int W, color C);

    void SendSelecteDown();

    void SendSelectedUp();

    void RotateSelected(int deg);

    void PrintSelected();

    Point MoveSelected(Point p);

    bool PasteClipboard(Point p);

    void ReturnMoved(Point p);

    void SetClipboard();
    void ApplicationManager::SetClipboard(multiset<CFigure*, CmpFigures> clip);

    multiset<CFigure*, CmpFigures> GetClipboard();

    vector<CFigure*> DeleteSelected();

    int Num_Selected;

private:
    multiset<CFigure*, CmpFigures> figs;
    multiset<CFigure*, CmpFigures> Clipboard;
    multiset<CFigure*, CmpFigures> Moved;

    CFigure* GetFigure(unsigned int id) const;

    // return iterator to the figure if found
    // if not found, returns figs.end()
    multiset<CFigure*, CmpFigures>::iterator GetFigureIter(unsigned int id) const;

    // for undo and redo
    stack<Action*> undo_st;
    stack<Action*> redo_st;

    unsigned int next_id = 0;

    //variable to indecate zooming state...zoom=0 -> no zoom at all, zoom=1 -> zoom_in x2, zoom=-1 -> zoom_out x0.5, etc
    int zoom = 0;
    Point manager_zoom_point;

    //Pointers to Input and Output classes
    Input* in_p;
    Output* out_p;
};

#endif