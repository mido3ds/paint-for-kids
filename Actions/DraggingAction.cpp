#include "DraggingAction.h"

DraggingAction::DraggingAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void DraggingAction::ReadActionParameters()
{
}

void DraggingAction::Execute()
{
    /* PSUEDO-CODE
        bool dragging = true;

        p = get_click_point();
        fig = DetectFigure();
        if (fig == null)
            return;

        Point& side_point = fig.GetClickedPoint(p);
        while (dragging)
        {
            if (not clicking)
            {
                dragging = false;
            }
            else 
            {
                side_point = p;
            }

            mang_p->UpdateInterface();
        }
    */

    
}

void DraggingAction::Undo()
{
}
