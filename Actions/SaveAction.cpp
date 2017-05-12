#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void SaveAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();

    string file_name = GetFileName();
    if (file_name == "")
        return;

    out_file.open(file_name, ofstream::out);

    if (!out_file.is_open()) {
        out_p->PrintMessage("Cant open file!");
		cerr << "unsuccessfull saving, something went wrong\n";
    } else {
        successfull = true;
    }

    out_p->ClearStatusBar();
}

void SaveAction::Execute()
{
    if (successfull) {
        manager_p->SaveAll(out_file);
        out_file.close();
    }
}

void SaveAction::Undo()
{
}

string SaveAction::GetFileName()
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

    if (GetSaveFileName(&ofn))
        return string(szFileName);
    else
        return "";
}