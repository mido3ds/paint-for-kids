/*
    stores actions to be undoed, redoed
*/
#ifndef __History_h__
#define __History_h__

#include "Actions/Action.h"
#include <stack>
#include <iostream> // cerr
using namespace std;

class History
{
public:
    History();
    ~History();
    
    // methods return true on success

    bool AddAction(Action*); // add given action to undo_stack if it can be undoed

    bool Undo(); // pop last action from undo_stack, undo it, push it to redo_stack
    bool Redo(); // reverse Undo

private:
    stack<Action*> undo_stack; 
    stack<Action*> redo_stack; 

};

#endif  /* __History_h__ */