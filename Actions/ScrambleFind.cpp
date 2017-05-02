#include "ScrambleFind.h"

ScrambleFind::ScrambleFind(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void ScrambleFind::ReadActionParameters()
{
}

void ScrambleFind::Execute()
{
    /*PSEUDO*/
    // resize the graph to half its size, put at left side 
    // create same graph at right side, but with random order
    // repeat until exit or switchDrawMode or finishs game:
        // from left side, chose randomly a figure, highlight it, and ask user to click on it 
        // both figures should disappeare when matching 
        // show counters for valid and invalid user trials 
    // diplay a final grade 
}

void ScrambleFind::Undo()
{
}