#include "ApplicationManager.h"

//Constructor
ApplicationManager::ApplicationManager()
{
    //Create Input and output
    out_p = new Output;
    in_p = out_p->CreateInput();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
    //Ask the input to get the action from the user.
    return in_p->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
// According to Action Type, return the corresponding action object
Action* ApplicationManager::DetectAction(ActionType act_type)
{
    switch (act_type) {
    case DRAW_RECT:
        return new AddRectAction(this);
    case DRAW_CIRC:
        return new AddCircAction(this);
    case DRAW_TRI:
        return new AddTrnglAction(this);
    case DRAW_LINE:
        return new AddLineAction(this);
	case RESIZE:
		return new ResizeAction(this);
	case ZOOM_IN:
		return new ZoomInAction(this);
	case ZOOM_OUT:
		return new ZoomOutAction(this);
    case EXIT:
        return new ExitAction(this);
    case TO_PLAY:
        return new SwitchPlayMode(this);
    case TO_DRAW:
        return new SwitchDrawMode(this);
    case SAVE:
        return new SaveAction(this);
    case LOAD:
        return new LoadAction(this);
    case UNDO:
        return new UndoAction(this);
    case REDO:
        return new RedoAction(this);
    case STATUS: //a click on the status bar ==> no action
        return nullptr;
    default:
        return nullptr;
    }
}
////////////////////////////////////////////////////////////////////////////////////
// gets action parameters and executes it
void ApplicationManager::ExecuteAction(ActionType act_type)
{
    Action* act_p = DetectAction(act_type);

	if (act_type == ZOOM_IN)
		zoom++;
	else if (act_type == ZOOM_OUT)
		zoom--;

    if (act_p != nullptr) {
        act_p->ReadActionParameters();

		if (act_type == ZOOM_IN)
		{
			ZoomInAction* zoom_in = dynamic_cast<ZoomInAction*>(act_p);
			manager_zoom_point = zoom_in->GetZoomPoint();
		}
		else if (act_type == ZOOM_OUT)
		{
			ZoomOutAction* zoom_out = dynamic_cast<ZoomOutAction*>(act_p);
			manager_zoom_point = zoom_out->GetZoomPoint();
		}

        act_p->Execute();

		if (zoom != 0)
		{
			CFigure* last_figure = GetFigure(figs.size() - 1);
			if (act_type == DRAW_LINE)
			{
				CLine* last_line = dynamic_cast<CLine*>(last_figure);

				last_line->p1.x = (last_line->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_line->p1.y = (last_line->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_line->p2.x = (last_line->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_line->p2.y = (last_line->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
			else if (act_type == DRAW_RECT)
			{
				CRectangle* last_rect = dynamic_cast<CRectangle*>(last_figure);

				last_rect->p1.x = (last_rect->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_rect->p1.y = (last_rect->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_rect->p2.x = (last_rect->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_rect->p2.y = (last_rect->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
			else if (act_type == DRAW_CIRC)
			{
				CCircle* last_circ = dynamic_cast<CCircle*>(last_figure);

				last_circ->p1.x = (last_circ->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_circ->p1.y = (last_circ->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_circ->p2.x = (last_circ->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_circ->p2.y = (last_circ->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
			else if (act_type == DRAW_TRI)
			{
				CTrngl* last_trngl = dynamic_cast<CTrngl*>(last_figure);

				last_trngl->p1.x = (last_trngl->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_trngl->p1.y = (last_trngl->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_trngl->p2.x = (last_trngl->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_trngl->p2.y = (last_trngl->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_trngl->p3.x = (last_trngl->p3.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_trngl->p3.y = (last_trngl->p3.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
		}

		// only add action if not (undo or redo or switchPlaymode or switchDrawMode)
		if (! (act_p->GetActType() == UNDO || act_p->GetActType() == REDO || act_p->GetActType() == TO_DRAW || act_p->GetActType() == TO_PLAY))
			undo_st.push(act_p);
    }
}
////////////////////////////////////////////////////////////////////////////////////
// gets action and executes it
void ApplicationManager::ExecuteAction(Action* act_p)
{

	ActionType act_type = act_p->GetActType();

	if (act_type == ZOOM_IN)
	{
		zoom++;
		ZoomInAction* zoom_in = dynamic_cast<ZoomInAction*>(act_p);
		manager_zoom_point = zoom_in->GetZoomPoint();
	}
	else if (act_type == ZOOM_OUT)
	{
		zoom--;
		ZoomOutAction* zoom_out = dynamic_cast<ZoomOutAction*>(act_p);
		manager_zoom_point = zoom_out->GetZoomPoint();
	}

	if (act_p != nullptr)
	{
		act_p->Execute();

		if (zoom != 0)
		{
			CFigure* last_figure = GetFigure(figs.size() - 1);
			if (act_type == DRAW_LINE)
			{
				CLine* last_line = dynamic_cast<CLine*>(last_figure);

				last_line->p1.x = (last_line->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_line->p1.y = (last_line->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_line->p2.x = (last_line->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_line->p2.y = (last_line->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
			else if (act_type == DRAW_RECT)
			{
				CRectangle* last_rect = dynamic_cast<CRectangle*>(last_figure);

				last_rect->p1.x = (last_rect->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_rect->p1.y = (last_rect->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_rect->p2.x = (last_rect->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_rect->p2.y = (last_rect->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
			else if (act_type == DRAW_CIRC)
			{
				CCircle* last_circ = dynamic_cast<CCircle*>(last_figure);

				last_circ->p1.x = (last_circ->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_circ->p1.y = (last_circ->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_circ->p2.x = (last_circ->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_circ->p2.y = (last_circ->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
			else if (act_type == DRAW_TRI)
			{
				CTrngl* last_trngl = dynamic_cast<CTrngl*>(last_figure);

				last_trngl->p1.x = (last_trngl->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_trngl->p1.y = (last_trngl->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_trngl->p2.x = (last_trngl->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_trngl->p2.y = (last_trngl->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

				last_trngl->p3.x = (last_trngl->p3.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
				last_trngl->p3.y = (last_trngl->p3.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
			}
		}
		// only add action if not (undo or redo or switchPlaymode or switchDrawMode)
		if (!(act_p->GetActType() == UNDO || act_p->GetActType() == REDO || act_p->GetActType() == TO_DRAW || act_p->GetActType() == TO_PLAY))
			undo_st.push(act_p);
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* fig_p)
{
    figs.insert(fig_p);
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
    //If a figure is found return a pointer to it.
    //if this point (x,y) does not belong to any figure return NULL

    ///Add your code here to search for a figure given a point x,y

    return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
// According to given string, return the corresponding Figure object
CFigure* ApplicationManager::DetectFigure(string fig_name)
{
    if (fig_name == "RECTANGLE")
        return new CRectangle();
    if (fig_name == "CIRCLE")
        return new CCircle();
    if (fig_name == "TRIANGLE")
        return new CTrngl();
    if (fig_name == "LINE")
        return new CLine();
    throw - 1;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	out_p->ClearDrawArea();
    for (auto& fig : figs)
        fig->Draw(out_p); //Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input* ApplicationManager::GetInput() const
{
    return in_p;
}
//Return a pointer to the output
Output* ApplicationManager::GetOutput() const
{
    return out_p;
}

int ApplicationManager::GetZoom() const
{
	return zoom;
}
////////////////////////////////////////////////////////////////////////////////////
Point ApplicationManager::GetManagerZoomPoint() const
{
	return manager_zoom_point;
}
////////////////////////////////////////////////////////////////////////////////////
// iterate through all figures
// call save for each one
void ApplicationManager::SaveAll(ofstream& out_file)
{
    // TODO
    out_file << UI.DrawColor.ucRed << ' '
             << UI.DrawColor.ucGreen << ' '
             << UI.DrawColor.ucBlue << ' '

             << UI.FillColor.ucRed << ' '
             << UI.FillColor.ucGreen << ' '
             << UI.FillColor.ucBlue << ' '

             << UI.BkGrndColor.ucRed << ' '
             << UI.BkGrndColor.ucGreen << ' '
             << UI.BkGrndColor.ucBlue << '\n';
    out_file << figs.size() << '\n';

    for (auto& fig : figs)
        fig->Save(out_file);
}
// iterate through lines and make the apropriate figure
// call load for the figure
void ApplicationManager::LoadAll(ifstream& in_file)
{
    // TODO
    int size = 0;
    string fig_name;
    CFigure* fig = nullptr;

    in_file >> UI.DrawColor.ucRed
        >> UI.DrawColor.ucGreen
        >> UI.DrawColor.ucBlue

        >> UI.FillColor.ucRed
        >> UI.FillColor.ucGreen
        >> UI.FillColor.ucBlue

        >> UI.BkGrndColor.ucRed
        >> UI.BkGrndColor.ucGreen
        >> UI.BkGrndColor.ucBlue;

    in_file >> size;

    for (int i = 0; i < size; i++) {
        in_file >> fig_name;
        fig = DetectFigure(fig_name);
        fig->Load(in_file);

        figs.insert(fig);
    }
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Undo()
{
	if (undo_st.empty())
		return;

    Action* to_undo = undo_st.top();

    to_undo->Undo();
    redo_st.push(to_undo);
    undo_st.pop();
}

void ApplicationManager::Redo()
{
	if (redo_st.empty())
		return;

    Action* to_redo = redo_st.top();

    //to_redo->Execute();
	ExecuteAction(to_redo);
    undo_st.push(to_redo);
    redo_st.pop();
}
////////////////////////////////////////////////////////////////////////////////////

unsigned int ApplicationManager::GenerateNextId()
{
    return next_id++;
}

void ApplicationManager::DeleteFigure(unsigned int id)
{
    auto itr = GetFigureIter(id);
    if (itr != figs.end())
    {
        delete (*itr);
        figs.erase(itr);
    }
    else
    {
        // cant delete figure not found
        throw -1;
    }
}

CFigure* ApplicationManager::GetFigure(unsigned int id) const
{
    for (auto& fig : figs)
        if (fig->GetId() == id)
            return fig;
    return nullptr;
}

multiset<CFigure*, CmpFigures>* ApplicationManager::GetFigures()
{
	return &figs;
}

multiset<CFigure*, CmpFigures>::iterator ApplicationManager::GetFigureIter(unsigned int id) const
{
    for (auto itr = figs.begin(); itr != figs.end(); itr++)
        if ((*itr)->GetId() == id)
            return itr;

    return figs.end();
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (auto& fig : figs)
		delete fig;
    delete in_p;
    delete out_p;
}
