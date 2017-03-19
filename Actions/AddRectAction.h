#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "Action.h"

//Add Rectangle Action class
class AddRectAction : public Action 
{
public:
    AddRectAction(ApplicationManager* app_p);

    //Reads rectangle parameters
    virtual void ReadActionParameters();

    //Add rectangle to the ApplicationManager
    virtual void Execute();
    
private:
    Point p1, p2; //Rectangle Corners
    GfxInfo rect_gfx_info;
};

#endif