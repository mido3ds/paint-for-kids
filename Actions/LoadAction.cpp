#include "LoadAction.h"

LoadAction::LoadAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void LoadAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

	// check to save if not 
	if (!manager_p->IsSaved())
	{
		out_p->PrintMessage("Do you need to save this graph before loading new? y/n");
		string input = in_p->GetString(out_p);
		if (input == "y" || input == "Y")
			manager_p->ExecuteAction(SAVE);
	}

    string file_name = GetFileName();
    if (file_name == "")
        return;

    in_file.open(file_name, ofstream::in);

    if (!in_file.is_open()) {
        out_p->PrintMessage("Cant open file!");
		cerr << "unsuccessfull loading, something went wrong\n";
    } else {
        successfull = true;
    }

    out_p->ClearStatusBar();
}

void LoadAction::Execute()
{
    if (successfull) {
		manager_p->DeleteAllFigures();
        manager_p->LoadAll(in_file);
        in_file.close();
    }
}

void LoadAction::Undo()
{
}

string LoadAction::GetFileName()
{
    // using WIN_API to open dialogue, see [http://www.winprog.org/tutorial/app_two.html] 

    OPENFILENAME ofn;

    const int MAX_PATH = 100;
    char szFileName[MAX_PATH] = ""; // TODO: make it string 

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";

    if (GetOpenFileName(&ofn))
        return string(szFileName);
    else
        return "";
}