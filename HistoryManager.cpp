#include "HistoryManager.h"

HistoryManager::HistoryManager() 
{}

HistoryManager::~HistoryManager()
{
    // remove & delete actions in stacks
    while (!undo_stack.empty()) {
        delete undo_stack.top();
        undo_stack.pop();
    }
    while (!redo_stack.empty()) {
        delete redo_stack.top();
        redo_stack.pop();
    }
}


bool HistoryManager::AddAction(Action* given_act)
{
	if (!given_act)
	{
        cerr << "null action was passed to Undo stack\n";
		return false;
	}

    if (given_act->CanUndo()) {
        undo_stack.push(given_act);
        return true;
    }

    return false;
}

bool HistoryManager::Undo()
{
    if (undo_stack.empty())
        return false;

    Action* to_undo = undo_stack.top();

    to_undo->Undo();
    redo_stack.push(to_undo);
    undo_stack.pop();

    return true;
}

bool HistoryManager::Redo()
{
    if (redo_stack.empty())
        return false;

    Action* to_redo = redo_stack.top();

    to_redo->Execute();
    undo_stack.push(to_redo);
    redo_stack.pop();

    return true;
}
