#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

// std 
#include <iostream> // cerr
#include <fstream> // fstream
#include <string>
#include <deque>
#include <vector>
#include <cmath>
#include <ctime>

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
#include "Actions/SendDownAction.h"
#include "Actions/SendUpAction.h"
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
#include "Actions/UndoAction.h"
#include "Actions/ZoomInAction.h"
#include "Actions/ZoomOutAction.h"
#include "Actions/DrawFigActions.h"
#include "Actions/DrawFigItems.h"
#include "Actions/ScrambleFind.h"
#include "Actions/PickAction.h"
#include "Actions/PickByColor.h"
#include "Actions/PickByType.h"
#include "Actions/PickByArea.h"
#include "Actions/PickByTypeAndColor.h"
#include "Actions/MultiSelect.h"

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
    static CFigure* GetFigure(const deque<CFigure*>& figs, Point p); // Search for a figure given a point inside the figure and the list
    int GetNumFigures() const;
    int GetNumSelected() const;
    void SetNumSelected(int n_selected); //Change number of selected figures
    void DeleteFigure(unsigned int id); // delete a figure given its stored id 
	void DeleteAllFigures(); // clear deque and deletes figures
    deque<CFigure*> GetCopyOfFigures(); // return a complete copy of all figures, for play mode

	bool UnselectAll();
    bool SetSelectedFillColor(color c);
    bool SetSelectedBorder(int W, color C);
    void SendSelecteDown();
    void SendSelectedUp();
    void RotateSelected(int deg);
    bool ResizeSelected(double resize_factor);
    void PrintSelectedSize();
    void MoveSelected(Point p, deque<CFigure*> &moved_figs,Point& old);
    deque<CFigure*> EraseSelected(); // erases selected and returns them 

    unsigned int GenerateNextId(); // returns next available id to assign to figure

    /*  ------------------------------- File ------------------------------- */ 

    void SaveAll(ofstream& out_file); // call save for figures
    void LoadAll(ifstream& in_file);  // call load for figures
    bool IsSaved() const; // if figures are saved or not 

    /*  ------------------------------- Interface ------------------------------- */ 

    void UpdateInterface() const; //Redraws all the drawing window
	void UpdateInterface(deque <CFigure *> figures);
    Input* GetInput() const; //Return pointer to the input
    Output* GetOutput() const; //Return pointer to the output

    /*  ------------------------------- clipboard ------------------------------- */ 

    bool PasteClipboard(Point p);
    void FillClipboardWithSelected(); 
    void SetClipboard(deque<CFigure*> clip);
    deque<CFigure*> GetClipboard();

	/*  ------------------------------- MultiSelect ------------------------------- */
	bool GetMultiSelect();
	void ToggleMultiSelect();

private:
    HistoryManager history;
    CFigure* GetFigure(unsigned int id) const;
    deque<CFigure*>::iterator 
        GetFigureIter(unsigned int id);  // return iterator to the figure if found, otherwise figs.end()
    
    deque<CFigure*> figs;
    
    deque<CFigure*> clipboard; 

    unsigned int next_fig_id = 0;  // saves last given id for a shape
	int num_selected = 0;

    bool figs_is_saved;  // whether figs has been saved or not

	bool multi_select = false;
	
    Input* in_p;
    Output* out_p;
};

#endif