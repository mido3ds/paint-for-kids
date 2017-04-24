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
        bar = 1;
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
        //out_p->ClearTToolBar();
        return nullptr;
    case CTR:
        bar = 2;
        out_p->CreateFigActions();
        return nullptr;
    case DEL:
        //out_p->ClearTToolBar();
        return new DeleteAction(this);
    case MOVE:
        //out_p->ClearTToolBar();
        return new MoveAction(this);
    case RESIZE:
        //out_p->ClearTToolBar();
        return new ResizeAction(this);
    case COPY:
        //out_p->ClearTToolBar();
        return new CopyAction(this);
    case PASTE:
        //out_p->ClearTToolBar();
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

    if (act_p != nullptr) {
        act_p->ReadActionParameters();
        act_p->Execute();

        // try to add action, else delete it
        if (!history.AddAction(act_p))
            delete act_p;
    }
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
	for (auto& fig : figs)
		fig->Draw(out_p); //Call Draw function (virtual member fn)

	if (bar == 1)
		out_p->CreateFigItems();
	else if (bar == 2)
		out_p->CreateFigActions();

	bar = 0;
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

////////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::GetBar() const
{
	return bar;
}
////////////////////////////////////////////////////////////////////////////////////
// iterate through all figures
// call save for each one
void ApplicationManager::SaveAll(ofstream& out_file)
{
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

unsigned int ApplicationManager::GenerateNextId()
{
    return next_fig_id++;
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

multiset<CFigure*, CmpFigures>::iterator ApplicationManager::GetFigureIter(unsigned int id) const
{
	for (auto itr = figs.begin(); itr != figs.end(); itr++)
		if ((*itr)->GetId() == id)
			return itr;

	return figs.end();
}

bool ApplicationManager::ResizeSelected(int resize_factor)
{
	bool flag = false;

	for (auto& fig : figs)
		if (fig->IsSelected())
		{
			fig->Resize(resize_factor);
			flag = true;
		}

	return flag;
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
			}
			else {
				out_p->PrintMessage("This Figure Is Out Of Range If Rotated");
			}
		}
	}
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

void ApplicationManager::PrintSelectedSize()
{
    if (Num_Selected != 0)
        out_p->PrintMessage("Number of selected figures are " + to_string(Num_Selected));
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
            moved_figs.insert(fig);
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
    for (auto& fig : clipboard) {
        Point c = fig->CalcCenter();
        if (c.x <= minx && c.y <= miny) {
            minx = c.x;
            miny = c.y;
        }
    }
    bool a = true;
    x = p.x - minx;
    y = p.y - miny; // difference between the new & old center of the first figure
    for (auto& fig : clipboard) {
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
    clipboard.clear();
    CFigure* copy;
    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            copy = fig->Copy();
            copy->SetId(GenerateNextId());
            clipboard.insert(copy);
        }
    }
}

void ApplicationManager::SetClipboard(multiset<CFigure*, CmpFigures> clip)
{
    clipboard = clip;
}
multiset<CFigure*, CmpFigures> ApplicationManager::GetClipboard()
{
    return clipboard;
}

vector<CFigure*> ApplicationManager::DeleteSelected()
{
    // TODO: why is this returning vec? it should do one thing
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
void ApplicationManager::Undo()
{
    history.Undo();
}

void ApplicationManager::Redo()
{
    history.Redo();
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
    // delete figs
    for (auto& fig : figs)
        delete fig;

    delete in_p;
    delete out_p;
}