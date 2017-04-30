#include "ApplicationManager.h"

//Constructor
ApplicationManager::ApplicationManager()
{
    //Create Input and output
    out_p = new Output;
    in_p = out_p->CreateInput();
    num_selected = 0;
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
    case DESELECT:
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
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* fig_p)
{
	figs.push_back(fig_p);
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

int ApplicationManager::GetNumFigures() const
{
	return figs.size();
}
////////////////////////////////////////////////////////////////////////////////////
// gets number of selected figures
int ApplicationManager::GetNumSelected() const
{
	return num_selected;
}
////////////////////////////////////////////////////////////////////////////////////
// sets number of selected figures
void ApplicationManager::SetNumSelected(int n_selected)
{
	num_selected = n_selected;
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
	cerr << "Detect figure has been given unknown fig_name as a parameter, fig_name = " << fig_name;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface()
{
	out_p->ClearDrawArea();

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

		figs.push_back(fig);
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
       // cerr << "Cant delete figure, figure not found, id = " << id << endl;
    }
}

CFigure* ApplicationManager::GetFigure(unsigned int id) const
{
	for (auto& fig : figs)
		if (fig->GetId() == id)
			return fig;
	return nullptr;
}

deque<CFigure*>::iterator ApplicationManager::GetFigureIter(unsigned int id)
{
	for (auto itr = figs.begin(); itr != figs.end(); itr++)
		if ((*itr)->GetId() == id)
			return itr;

	return figs.end();
}

bool ApplicationManager::ResizeSelected(double resize_factor)
{
	bool flag = false;

	for (auto& fig : figs)
	{
		if (fig->IsSelected())
		{
			fig->Resize(resize_factor);
			flag = true;
		}
	}
	return flag;
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

            flag = true;
        }
    }

    return flag;
}

bool ApplicationManager::DeselectAll()
{
	bool found_selected = false;
	for (auto& fig : figs)
	{
		found_selected = true;
		fig->SetSelected(false);
	}
	num_selected = 0;
	return found_selected;
}

void ApplicationManager::SendSelecteDown()
{
    // TODO: test
	vector<CFigure*> temp;
    for (auto itr = figs.begin(); itr != figs.end();)
    {
        if ((*itr)->IsSelected())
        {
            temp.push_back(*itr);
            itr = figs.erase(itr);
			continue;
        }
		++itr;
    }

	for (auto& fig : temp)
		figs.push_front(fig);
}

void ApplicationManager::SendSelectedUp()
{
	vector<CFigure*> temp;
	for (auto itr = figs.begin(); itr != figs.end();)
	{
		if ((*itr)->IsSelected())
		{
			temp.push_back(*itr);
			itr = figs.erase(itr);
			continue;
		}
		++itr;
	}

	for (auto& fig : temp)
		figs.push_back(fig);
}

void ApplicationManager::PrintSelectedSize()
{
	if (num_selected == 1)
	{
		CFigure *selected;
		for (auto& fig : figs)
		{
			if (fig->IsSelected()) 
			{
				selected = fig;
				break;
			}
		}
		selected->PrintInfo(out_p);
	}
	else if (num_selected > 0)  out_p->PrintMessage("Number of selected figures are " + to_string(num_selected));
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
			fig->SetSelected(true);
            moved_figs.push_back(fig);
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
		CFigure*copy = fig->Copy();
		copy->SetId(GenerateNextId());
        AddFigure(copy);
		fig->SetId(copy->GetId());

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
			copy->SetSelected(false);
            clipboard.push_back(copy);
        }
    }
}

void ApplicationManager::SetClipboard(deque<CFigure*> clip)
{
    clipboard = clip;
}

deque<CFigure*> ApplicationManager::GetClipboard()
{
    return clipboard;
}

deque<CFigure*> ApplicationManager::DeleteSelected()
{
    // TODO: why is this returning vec? it should do one thing
    deque<int> vec;
    deque<CFigure*> deleted;
    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            vec.push_back(fig->GetId());
			CFigure*copy = fig->Copy();
            deleted.push_back(copy);
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        DeleteFigure(vec[i]);
		num_selected--;
    }
    return deleted;
}
////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::DeleteAllFigures()
{
	for (auto& fig : figs)
		delete fig;
	figs.clear();
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
	DeleteAllFigures();

    delete in_p;
    delete out_p;
}