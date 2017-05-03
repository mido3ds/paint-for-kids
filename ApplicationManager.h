#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

// std 
#include <iostream> // cerr, TODO: redirect cerr to a log file
#include <fstream> // fstream
#include <string>
#include <deque> // double-ended-queue; to insert at beginning and end
#include <vector>
#include <cmath>

// actions
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
#include "Actions/DrawFigActions.h"
#include "Actions/DrawFigItems.h"
#include "Actions/ScrambleFind.h"

// figures
#include "Figures/CCircle.h"
#include "Figures/CFigure.h"
#include "Figures/CLine.h"
#include "Figures/CRectangle.h"
#include "Figures/CTrngl.h"

// other
#include "DEFS.h"
#include "HistoryManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

class ApplicationManager {
public:
	ApplicationManager();
	~ApplicationManager();
    /*  ------------------------------- DEPRECATED ------------------------------- */ 

    void ReturnMoved(Point p); // no return --bad name-- + it calls other function --redundant--

    /*  ------------------------------- Actions ------------------------------- */ 

    ActionType GetUserAction() const; // Reads the input command from the user and returns the corresponding action type
    Action* DetectAction(ActionType act_type); // return action object from action enum
    void ExecuteAction(ActionType); // execute given action 

    void Undo();
    void Redo();

    /*  ------------------------------- Figures ------------------------------- */ 

    void AddFigure(CFigure* fig_p); // Adds a new figure to the figs
    CFigure* DetectFigure(string fig_name); // make new figure from its name
    CFigure* GetFigure(int x, int y) const; // return figure at that point, for this->figs
    static CFigure* GetFigure(deque<CFigure*> figs, Point p); // Search for a figure given a point inside the figure and the list
    int GetNumFigures() const;
    int GetNumSelected() const;
    void SetNumSelected(int n_selected); //Change number of selected figures
    void DeleteFigure(unsigned int id); // delete a figure given its stored id 
	void DeleteAllFigures(); // clear deque and deletes figures
    deque<CFigure*> GetCopyOfFigures(); // return a complete copy of all figures, for play mode

	bool DeselectAll();
    bool ChangeSelectedFillColor(color c);
    bool ChangeSelectedBorder(int W, color C);
    void SendSelecteDown();
    void SendSelectedUp();
    void RotateSelected(int deg);
    bool ResizeSelected(double resize_factor);
    void PrintSelectedSize();
    Point MoveSelected(Point p);
    deque<CFigure*> DeleteSelected(); // TODO: it should be void DeleteSelected()

    unsigned int GenerateNextId(); // returns next available id to assign to figure

    /*  ------------------------------- File ------------------------------- */ 

    void SaveAll(ofstream& out_file); // call save for figures
    void LoadAll(ifstream& in_file);  // call load for figures

    /*  ------------------------------- Interface ------------------------------- */ 

    void UpdateInterface(); //Redraws all the drawing window // TODO: make it const method
    Input* GetInput() const; //Return pointer to the input
    Output* GetOutput() const; //Return pointer to the output
    int GetZoom() const; //Return value of zoom
    Point GetManagerZoomPoint() const; //Return zooming point if there was zooming

    /*  ------------------------------- clipboard ------------------------------- */ 

    bool PasteClipboard(Point p);
    void SetClipboard();    // TODO why two methods ?
    void SetClipboard(deque<CFigure*> clip);
    deque<CFigure*> GetClipboard();

private:
    HistoryManager history;
    CFigure* GetFigure(unsigned int id) const;
    deque<CFigure*>::iterator 
        GetFigureIter(unsigned int id);  // return iterator to the figure if found, otherwise figs.end()
    
    deque<CFigure*> figs;
    deque<CFigure*> moved_figs;
    deque<CFigure*> clipboard; 

    unsigned int next_fig_id = 0;  // saves last given id for a shape
	int num_selected = 0;

    Input* in_p;
    Output* out_p;
};

#endif