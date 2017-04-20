#include "ApplicationManager.h"

//Constructor
ApplicationManager::ApplicationManager()
{
    //Create Input and output
    out_p = new Output;
    in_p = out_p->CreateInput();
    Num_Selected = 0;
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
    case DRAW_FIG_ITM:
        out_p->CreateFigItems();
        return nullptr;
    case DRAW_RECT:
        return new AddRectAction(this);
    case DRAW_CIRC:
        return new AddCircAction(this);
    case DRAW_TRI:
        return new AddTrnglAction(this);
    case DRAW_LINE:
        return new AddLineAction(this);
    case ZOOM_IN:
        return new ZoomInAction(this);
    case ZOOM_OUT:
        return new ZoomOutAction(this);
    case EXIT:
        return new ExitAction(this);
    case TO_PLAY:
        return new ToPlayModeAction(this);
    case TO_DRAW:
        return new ToDrawModeAction(this);
    case SAVE:
        return new SaveAction(this);
    case LOAD:
        return new LoadAction(this);
    case UNDO:
        return new UndoAction(this);
    case REDO:
        return new RedoAction(this);
    case CHNG_FILL_CLR:
        return new ChFillColorAction(this);
    case CHNG_BK_CLR:
        return new ChBGColorAction(this);
    case CHNG_DRAW_CLR:
        return new ChBorderAction(this);
    case SEND_BACK:
        return new DownAction(this);
    case BRNG_FRNT:
        return new UpAction(this);
    case ROTATE:
        return new RotateAction(this);
    case COLOR_BAR:
        out_p->ClearTToolBar();
        return nullptr;
    case CTR:
        out_p->CreateFigActions();
        return nullptr;
    case DEL:
        out_p->ClearTToolBar();
        return new DeleteAction(this);
    case MOVE:
        out_p->ClearTToolBar();
        return new MoveAction(this);
    case RESIZE:
        out_p->ClearTToolBar();
        return new ResizeAction(this);
    case COPY:
        out_p->ClearTToolBar();
        return new CopyAction(this);
    case PASTE:
        out_p->ClearTToolBar();
        return new PasteAction(this);
    case SELECT:
        return new SelectAction(this);
    case UNSELECT:
        return new UnSelectAction(this);
    case CUT:
        return new CutAction(this);

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

        if (act_type == ZOOM_IN) {
            ZoomInAction* zoom_in = dynamic_cast<ZoomInAction*>(act_p);
            manager_zoom_point = zoom_in->GetZoomPoint();
        } else if (act_type == ZOOM_OUT) {
            ZoomOutAction* zoom_out = dynamic_cast<ZoomOutAction*>(act_p);
            manager_zoom_point = zoom_out->GetZoomPoint();
        }

        act_p->Execute();

        if (zoom != 0) {
            CFigure* last_figure = GetFigure(figs.size() - 1);
            if (act_type == DRAW_LINE) {
                CLine* last_line = dynamic_cast<CLine*>(last_figure);

                last_line->p1.x = (last_line->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_line->p1.y = (last_line->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

                last_line->p2.x = (last_line->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_line->p2.y = (last_line->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
            } else if (act_type == DRAW_RECT) {
                CRectangle* last_rect = dynamic_cast<CRectangle*>(last_figure);

                last_rect->p1.x = (last_rect->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_rect->p1.y = (last_rect->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

                last_rect->p2.x = (last_rect->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_rect->p2.y = (last_rect->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
            } else if (act_type == DRAW_CIRC) {
                CCircle* last_circ = dynamic_cast<CCircle*>(last_figure);

                last_circ->p1.x = (last_circ->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_circ->p1.y = (last_circ->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

                last_circ->p2.x = (last_circ->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_circ->p2.y = (last_circ->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
            } else if (act_type == DRAW_TRI) {
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
        // TODO make it better, you may check if action is a draw add it, and ignore others or make draw action add itself to the stack
        if (!(Action::IsFromAction<UndoAction>(act_p)
                || Action::IsFromAction<RedoAction>(act_p)
                || Action::IsFromAction<ToDrawModeAction>(act_p)
                || Action::IsFromAction<ToPlayModeAction>(act_p)
                || Action::IsFromAction<SaveAction>(act_p)
                || Action::IsFromAction<LoadAction>(act_p)))
            undo_st.push(act_p);
        else
            delete act_p;
    }
}
////////////////////////////////////////////////////////////////////////////////////
// gets action and executes it
// TODO remove this function
void ApplicationManager::ExecuteAction(Action* act_p)
{
    // GetActType is obsolete and deleted it cannot be used
    //ActionType act_type = act_p->GetActType();

    // i have put this just to run the program untill it is removed
    ActionType act_type = ActionType::EMPTY;

    if (act_type == ZOOM_IN) {
        zoom++;
        ZoomInAction* zoom_in = dynamic_cast<ZoomInAction*>(act_p);
        manager_zoom_point = zoom_in->GetZoomPoint();
    } else if (act_type == ZOOM_OUT) {
        zoom--;
        ZoomOutAction* zoom_out = dynamic_cast<ZoomOutAction*>(act_p);
        manager_zoom_point = zoom_out->GetZoomPoint();
    }

    if (act_p != nullptr) {
        act_p->Execute();

        if (zoom != 0) {
            CFigure* last_figure = GetFigure(figs.size() - 1);
            if (act_type == DRAW_LINE) {
                CLine* last_line = dynamic_cast<CLine*>(last_figure);

                last_line->p1.x = (last_line->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_line->p1.y = (last_line->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

                last_line->p2.x = (last_line->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_line->p2.y = (last_line->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
            } else if (act_type == DRAW_RECT) {
                CRectangle* last_rect = dynamic_cast<CRectangle*>(last_figure);

                last_rect->p1.x = (last_rect->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_rect->p1.y = (last_rect->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

                last_rect->p2.x = (last_rect->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_rect->p2.y = (last_rect->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
            } else if (act_type == DRAW_CIRC) {
                CCircle* last_circ = dynamic_cast<CCircle*>(last_figure);

                last_circ->p1.x = (last_circ->p1.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_circ->p1.y = (last_circ->p1.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;

                last_circ->p2.x = (last_circ->p2.x - manager_zoom_point.x) / pow(2, zoom) + manager_zoom_point.x;
                last_circ->p2.y = (last_circ->p2.y - manager_zoom_point.y) / pow(2, zoom) + manager_zoom_point.y;
            } else if (act_type == DRAW_TRI) {
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
        // TODO make it better, you may check if action is a draw add it, and ignore others or make draw action add itself to the stack
        if (!(Action::IsFromAction<UndoAction>(act_p)
                || Action::IsFromAction<RedoAction>(act_p)
                || Action::IsFromAction<ToDrawModeAction>(act_p)
                || Action::IsFromAction<ToPlayModeAction>(act_p)
                || Action::IsFromAction<SaveAction>(act_p)
                || Action::IsFromAction<LoadAction>(act_p)))
            undo_st.push(act_p);
        else
            delete act_p;
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
    Point p;
    p.x = x;
    p.y = y;
    unsigned int max_z = 0, id = 0;

    for (auto& fig : figs) {
        if (fig->PointCheck(p) && fig->z_index >= max_z) {
            max_z = fig->z_index;
            id = fig->GetId();
        }
    }
    return GetFigure(id);
    return nullptr;
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
void ApplicationManager::UpdateInterface()
{
    // TODO: there is a better approach
    if (GetZoom() > 0) {
        ZoomInAction zoom_in(this);
        zoom_in.SetZoomFactor(pow(2, GetZoom()));
        zoom_in.SetZoompoint(GetManagerZoomPoint());
        zoom_in.Execute();
    } else if (GetZoom() < 0) {
        ZoomOutAction zoom_out(this);
        zoom_out.SetZoomFactor(pow(2, GetZoom()));
        zoom_out.SetZoompoint(GetManagerZoomPoint());
        zoom_out.Execute();
    } else {
        for (auto& fig : figs)
            fig->Draw(out_p); //Call Draw function (virtual member fn)
    }
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

    to_redo->Execute();
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
    if (itr != figs.end()) {
        delete (*itr);
        figs.erase(itr);
    } else {
        // cant delete figure not found
        throw - 1;
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

bool ApplicationManager::ChangeSelectedFillColor(color c)
{
    bool flag = false;

    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            fig->ChngFillClr(c);

            flag = true;
        }
    }

    return flag;
}

bool ApplicationManager::ChangeSelectedBorder(int W, color C)
{
    bool flag = false;

    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            fig->ChngDrawClr(C);
            fig->ChngBorderWidth(W);
            fig->SetSelected(false);

            flag = true;
        }
    }

    return flag;
}

void ApplicationManager::SendSelecteDown()
{
    // TODO: to be changed after making figs a vector not set
    int x;
    for (auto itr = figs.begin(); itr != figs.end(); itr++) {
        if ((*itr)->IsSelected()) {
            x = (*itr)->z_index;
            for (auto itr2 = figs.begin(); itr2 != figs.end(); itr2++) {
                if (x >= (*itr2)->z_index && itr != itr2) {
                    x = (*itr2)->z_index - 1;
                }
            }
            (*itr)->ChngZindex(x);
            (*itr)->SetSelected(false);
            multiset<CFigure*, CmpFigures> list(figs.begin(), figs.end());
            figs = list;
            itr = figs.begin();
        }
    }
}

void ApplicationManager::SendSelectedUp()
{
    // TODO: to be changed after making figs a vector not set
    int x;
    for (auto itr = figs.begin(); itr != figs.end(); itr++) {
        if ((*itr)->IsSelected()) {
            x = (*itr)->z_index;
            for (auto itr2 = figs.begin(); itr2 != figs.end(); itr2++) {
                if (x <= (*itr2)->z_index && itr != itr2) {
                    x = (*itr2)->z_index + 1;
                }
            }
            (*itr)->ChngZindex(x);
            (*itr)->SetSelected(false);
            multiset<CFigure*, CmpFigures> list(figs.begin(), figs.end());
            figs = list;
            itr = figs.begin();
        }
    }
}

void ApplicationManager::RotateSelected(int deg)
{
    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            fig->Rotate(deg);
            if (fig->IsRotate()) {
                fig->Rotated(false);
            } else {
                out_p->PrintMessage("This Figure Is Out Of Range If Rotated");
            }
        }
    }
}

void ApplicationManager::PrintSelected()
{

    if (Num_Selected != 1)
        out_p->PrintMessage("Number of selected figures are ");
}
Point ApplicationManager::MoveSelected(Point p) //list is M when moving and P when pasting
{

    int minx = UI.DrawAreaWidth, miny = UI.DrawAreaHeight; //coordinates of the center of the first figure
    int x = 0, y = 0;

    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            if ((fig->CalcCenter()).x <= minx && (fig->CalcCenter()).y <= miny) {
                minx = (fig->CalcCenter()).x;
                miny = (fig->CalcCenter()).y;
            }
        }
    }
    x = p.x - minx;
    y = p.y - miny; // difference between the new & old center of the first figure

    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            fig->Move(x, y);
            Moved.insert(fig);
        }
    }
    p.x = minx;
    p.y = miny;
    return p;
}

bool ApplicationManager::PasteClipboard(Point p)
{

    int minx = UI.DrawAreaWidth, miny = UI.DrawAreaHeight; //coordinates of the center of the first figure
    int x = 0, y = 0;
    for (auto& fig : Clipboard) {
        Point c = fig->CalcCenter();
        if (c.x <= minx && c.y <= miny) {
            minx = c.x;
            miny = c.y;
        }
    }
    bool a = true;
    x = p.x - minx;
    y = p.y - miny; // difference between the new & old center of the first figure
    for (auto& fig : Clipboard) {
        if (!fig->Move(x, y))
            a = false;
        AddFigure(fig);
    }
    return a;
}

void ApplicationManager::ReturnMoved(Point p)
{
    MoveSelected(p); //p is the old center of moved figures
}

void ApplicationManager::SetClipboard()
{
    Clipboard.clear();
    CFigure* copy;
    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            copy = fig->Copy();
            copy->SetId(GenerateNextId());
            Clipboard.insert(copy);
        }
    }
}
void ApplicationManager::SetClipboard(multiset<CFigure*, CmpFigures> clip)
{
    Clipboard = clip;
}
multiset<CFigure*, CmpFigures> ApplicationManager::GetClipboard()
{
    return Clipboard;
}

vector<CFigure*> ApplicationManager::DeleteSelected()
{
    vector<int> vec;
    vector<CFigure*> deleted;
    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            vec.push_back(fig->GetId());
            deleted.push_back(fig->Copy());
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        DeleteFigure(vec[i]);
    }
    return deleted;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
    // delete figs
    for (auto& fig : figs)
        delete fig;

    // remove actions in stacks
    while (!undo_st.empty()) {
        delete undo_st.top();
        undo_st.pop();
    }
    while (!redo_st.empty()) {
        delete redo_st.top();
        redo_st.pop();
    }

    delete in_p;
    delete out_p;
}