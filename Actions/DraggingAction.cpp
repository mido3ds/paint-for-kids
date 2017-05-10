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
        dragging = true;

        p = get_click_point()
        fig = get_figure()
        if (fig == null)
            return;

        if fig.IsCorner(p):
            p_to_update = fig.GetCornerPoint(p)
        else if fig.IsInside(p):
            p_to_update = fig.GetCenter(p)
        else: // outside
            return;
            
        while dragging:
            if not clicking:
                dragging = false;
            else:
                p_to_update = p;

            mang_p->UpdateInterface();
    */
    in_p = manager_p->GetInput();
    p = in_p->GetLastClickedPoint();

    fig = manager_p->GetFigure(p.x, p.y);
    if (fig == nullptr) // not found
        return;

    // loops depending on point relative position to fig
    switch (fig->GetPointState(p))  
    {
        case PointState::CORNER:
            ResizeByDragging();
			break;
        case PointState::INSIDE:
            MoveByDragging();
			break;
    }
}

void DraggingAction::Undo()
{
}

void DraggingAction::ResizeByDragging()
{
    // TODO
    // Point& corner_p = fig->GetCornerPoint(p);
    // while (still_clicking())
    // {
    //     p = GetCurrentMousePos();

    //     corner_p = p;

    //     manager_p->UpdateInterface();
    // }
}

void DraggingAction::MoveByDragging()
{
    // TODO
    // while (still_clicking())
    // {
    //     p = GetCurrentMousePos();

    //     fig->ChangeCenter(p);

    //     manager_p->UpdateInterface();
    // }
}
