#include "ApplicationManager.h"

//Constructor
ApplicationManager::ApplicationManager()
{
    //Create Input and output
    out_p = new Output;
    in_p = out_p->CreateInput();

    num_selected = 0;

    // make the seed of the pseudo-random generator
	time_t rawtime = time(0);
    srand(rawtime);

    // at beginning, figs is saved, as we dont have any yet
    figs_is_saved = true;

	// open log file, and redirect cerr,clog to it
	freopen("log.txt", "a", stderr);

	cerr << "\n***********************\n"
		<< "Application started at " << ctime(&rawtime)
		<< "this is a log file, for debugging\n"
		<< "***********************\n";
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
        return new DrawFigItems(this);
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
        return new SendDownAction(this);
    case BRNG_FRNT:
        return new SendUpAction(this);
    case ROTATE:
        return new RotateAction(this);
    case CTR:
        return new DrawFigActions(this);
    case DEL:
        return new DeleteAction(this);
    case MOVE:
        return new MoveAction(this);
    case RESIZE:
        return new ResizeAction(this);
    case COPY:
        return new CopyAction(this);
    case PASTE:
        return new PasteAction(this);
    case SELECT:
        return new SelectAction(this);
    case DESELECT:
        return new UnselectAction(this);
    case CUT:
        return new CutAction(this);
	case SCRAMBLE:
		return new ScrambleFind(this);
	case HIDE:
		return new PickAction(this);
	case PICK_COLOR:
		return new PickByColor(this);
	case PICK_TYPE:
		return new PickByType(this);
	case PICK_AREA:
		out_p->PrintMessage("Picking By Area");		// Just For Testing
		return nullptr;
	case PICK_COL_TYP:
		out_p->PrintMessage("Picking By Color And Type");		// Just For Testing
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

    if (act_p != nullptr) {
        act_p->ReadActionParameters();
        act_p->Execute();

        // try to add action, else delete it
        if (!history.AddAction(act_p))
        {
            delete act_p;

            // action must have changed figs
            figs_is_saved = false; 
        }
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
CFigure* ApplicationManager::GetFigure(const deque<CFigure*>& figs, Point p)
{
    // reverse iterator, to iterate in figs from end to beginning 
    for (deque<CFigure*>::const_reverse_iterator r_itr = figs.rbegin();r_itr != figs.rend(); r_itr++)
    {
        // if a figure is found return a pointer to it.
        if ((*r_itr)->IsPointInside(p))
            return *r_itr;
    }

    // (x,y) does not belong to any figure
    return nullptr;
}

CFigure* ApplicationManager::GetFigure(int x, int y) const
{
    return ApplicationManager::GetFigure(figs, { x, y });
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
void ApplicationManager::UpdateInterface() const
{
	out_p->ClearDrawArea();

	for (auto& fig : figs)
		fig->Draw(out_p);

	if (UI.InterfaceMode == MODE_DRAW)
		out_p->CreateDrawToolBar();
	else
		out_p->CreatePlayToolBar();

	out_p->ClearStatusBar();
}

void ApplicationManager::UpdateInterface(deque<CFigure*> figures)
{
	out_p->ClearDrawArea();

	for (auto& fig : figures)
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

    figs_is_saved = true;
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

    figs_is_saved = true;
}

bool ApplicationManager::IsSaved() const
{
    // why consider saved if figs is empty? because if empty so no need to say you should save it
    return figs_is_saved || figs.empty(); 
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
        cerr << "Cant delete figure, figure not found, id = " << id << endl;
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
			if (fig->IsRotated()) {
				fig->SetRotated(false);
			}
			else {
				out_p->PrintMessage("This Figure Is Out Of Range If Rotated");
			}
		}
	}
}

bool ApplicationManager::SetSelectedFillColor(color c)
{
    bool flag = false;

    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            fig->SetFillColor(c);

            flag = true;
        }
    }

    return flag;
}

bool ApplicationManager::SetSelectedBorder(int W, color C)
{
    bool flag = false;

    for (auto& fig : figs) {
        if (fig->IsSelected()) {
            fig->SetDrawColor(C);
            fig->SetBorderWidth(W);

            flag = true;
        }
    }

    return flag;
}

bool ApplicationManager::UnselectAll()
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
            if ((fig->CalculateCenter()).x <= minx && (fig->CalculateCenter()).y <= miny) {
                minx = (fig->CalculateCenter()).x;
                miny = (fig->CalculateCenter()).y;
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
        Point c = fig->CalculateCenter();
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

void ApplicationManager::FillClipboardWithSelected()
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

deque<CFigure*> ApplicationManager::EraseSelected()
{
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

deque<CFigure*> ApplicationManager::GetCopyOfFigures()
{
    deque<CFigure*> result;

    for (auto& fig : figs)
        result.push_back(fig->Copy());

    return result;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	DeleteAllFigures();

    delete in_p;
    delete out_p;
}