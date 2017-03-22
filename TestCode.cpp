/*
    Phase1: test the Input and Output classes
    to move to phase2, comment next define
*/
#define PHASE1

#include "GUI/Input.h"
#include "GUI/Output.h"

#ifdef PHASE1

int main()
{
    int x, y;

    // Create Input and Output objects to test
    Output* out_p = new Output();
    Input* in_p = out_p->CreateInput();

    // Starting the test
    out_p->PrintMessage("This demo is to test input and output classes, Click "
                        "anywhere to start the test");
    in_p->GetPointClicked(x, y); // Wait for any click

    ///////////////////////////////////////////////////////////////////////////////////
    // TEST 1:
    //			Create The FULL Tool bar, the drawing area and the status
    //bar
    //			This has already been done through the constrcutor of class
    //Output
    ///////////////////////////////////////////////////////////////////////////////////

    out_p->PrintMessage(
        "TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
    in_p->GetPointClicked(x, y); // Wait for any click

    ///////////////////////////////////////////////////////////////////////////////////
    // TEST 2:
    //			Drawing all the Figures with all possible states:
    //			Non-filled, Filled, and highlighted in both cases
    ///////////////////////////////////////////////////////////////////////////////////

    out_p->PrintMessage("TEST2: Now we will show that Output class can draw any "
                        "figure in any state, Click anywhere to continue");
    in_p->GetPointClicked(x, y); // Wait for any click

    GfxInfo gfxInfo; // to be used with draw function of the class Ouput

    /// 2.1- CRectangle Test ///
    /// ===================
    out_p->PrintMessage("Drawing a CRectangle, filled/non-filled and Highlighted "
                        "filled/non-filled,  Click to continue");
    Point p1, p2, p3;
    gfxInfo.border_width = 3;
    gfxInfo.draw_clr = BLACK; // any color for border
    gfxInfo.is_filled = false; // CFigure is NOT filled
    out_p->PrintMessage("Action: Draw a CRectangle , Click anywhere");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: Draw a CRectangle , Click anywhere else -_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawRect(p1, p2, gfxInfo, false);
    out_p->PrintMessage("Action: highlighting , click anywhere -_--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: highlighting , click anywhere else -_--_--_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawRect(p1, p2, gfxInfo, true);
    out_p->PrintMessage("Action: filling , click anywhere  -_--_--_--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: filling , click anywhere else -_____-");
    in_p->GetPointClicked(p2.x, p2.y);
    gfxInfo.border_width = 4;
    gfxInfo.draw_clr = BLUE; // any color for border
    gfxInfo.fill_clr = GREEN; // any color for filling
    gfxInfo.is_filled = true; // CFigure is filled
    out_p->DrawRect(p1, p2, gfxInfo, false);
    out_p->PrintMessage("Action: filling highlighting , click anywhere -_____--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: filling highlighting , click anywhere else -_____--_--_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawRect(p1, p2, gfxInfo, true);
    gfxInfo.is_filled = false;
    out_p->PrintMessage(
        "Drawing a CRectangle Test ==> OK,  Click anywhere to continue");
    in_p->GetPointClicked(x, y); // Wait for any click
    out_p->ClearDrawArea();
    /// 2.2- Line Test ///
    /// ==============
    out_p->PrintMessage(
        "Drawing a Line, normal and Highlighted, Click to continue");
    out_p->PrintMessage("Action: Draw a Line , Click anywhere");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: Draw a Line , Click anywhere else -_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawLine(p1, p2, gfxInfo, false);
    out_p->PrintMessage("Action: highlighting click anywhere -_--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: highlighting click anywhere else -_--_--_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawLine(p1, p2, gfxInfo, true);
    /// TODO: Add code to draw Line, Normal and Highlighted

    out_p->PrintMessage("Drawing a Line Test ==> OK,  Click anywhere to continue");
    in_p->GetPointClicked(x, y); // Wait for any click
    out_p->ClearDrawArea();

    /// 2.3- Triangle Test ///
    /// ===================
    out_p->PrintMessage("Drawing a Triangle, filled/non-filled and Highlighted "
                        "filled/non-filled,  Click to continue");
    out_p->PrintMessage("Action: Draw a Triangle , Click anywhere");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: Draw a Circle , Click anywhere else -_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->PrintMessage("Action: Draw a Circle , Click anywhere else -_--_-");
    in_p->GetPointClicked(p3.x, p3.y);
    out_p->DrawTriangle(p1, p2, p3, gfxInfo, false);
    out_p->PrintMessage("Action: highlighting , click anywhere -_--_--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: highlighting , click anywhere else -_--_--_--_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->PrintMessage("Action: highlighting , click anywhere else -_____-");
    in_p->GetPointClicked(p3.x, p3.y);
    out_p->DrawTriangle(p1, p2, p3, gfxInfo, true);
    out_p->PrintMessage("Action: filling , click anywhere  -_____--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: filling , click anywhere else -_____--_--_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->PrintMessage("Action: filling , click anywhere else -_____--_--_--_-");
    in_p->GetPointClicked(p3.x, p3.y);
    gfxInfo.is_filled = true;
    out_p->DrawTriangle(p1, p2, p3, gfxInfo, false);
    out_p->PrintMessage("Action: filling highlighting , click anywhere -_____--_--_--_--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: filling highlighting , click anywhere else -__________-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->PrintMessage("Action: filling highlighting , click anywhere else -__________--_-");
    in_p->GetPointClicked(p3.x, p3.y);
    out_p->DrawTriangle(p1, p2, p3, gfxInfo, true);
    gfxInfo.is_filled = false;
    /// TODO: Add code to draw Triangle in all possible states

    out_p->PrintMessage(
        "Drawing a Triangle Test ==> OK,  Click anywhere to continue");
    in_p->GetPointClicked(x, y); // Wait for any click
    out_p->ClearDrawArea();

    /// 2.4- Circle Test ///
    /// ===================
    out_p->PrintMessage("Drawing a Circle, filled/non-filled and Highlighted "
                        "filled/non-filled,  Click to continue");
    out_p->PrintMessage("Action: Draw a Circle , Click anywhere");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: Draw a Circle , Click anywhere else -_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawCircle(p1, p2, gfxInfo, false);
    out_p->PrintMessage("Action: highlighting , click anywhere -_--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: highlighting , click anywhere else -_--_--_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawCircle(p1, p2, gfxInfo, true);
    out_p->PrintMessage("Action: filling , click anywhere  -_--_--_--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: filling , click anywhere else -_____-");
    in_p->GetPointClicked(p2.x, p2.y);
    gfxInfo.is_filled = true;
    out_p->DrawCircle(p1, p2, gfxInfo, false);
    out_p->PrintMessage("Action: filling highlighting , click anywhere -_____--_-");
    in_p->GetPointClicked(p1.x, p1.y);
    out_p->PrintMessage("Action: filling highlighting , click anywhere else -_____--_--_-");
    in_p->GetPointClicked(p2.x, p2.y);
    out_p->DrawCircle(p1, p2, gfxInfo, true);
    gfxInfo.is_filled = false;
    /// TODO: Add code to draw Circle in all possible states

    out_p->PrintMessage(
        "Drawing a Circle Test ==> OK,  Click anywhere to continue");
    in_p->GetPointClicked(x, y); // Wait for any click
    out_p->ClearDrawArea();

    ///////////////////////////////////////////////////////////////////////////////////
    // TEST 3:
    //			Input Class: Read strings from the user
    ///////////////////////////////////////////////////////////////////////////////////
    out_p->PrintMessage(
        "TEST3: Now Time to test class Input, Click anywhere to continue");
    in_p->GetPointClicked(x, y); // Wait for any click

    /// TODO: Add code here to
    // 1- Read a string from the user on the status bar
    // 2- After reading the stirng clear the status bar
    // 3- print on the status bar "You Entered" then print the string

    out_p->PrintMessage("Testing Input ability to read strings");
    string str = in_p->GetSrting(out_p);
    str = "you Entered " + str;
    out_p->PrintMessage(str.c_str());

    in_p->GetPointClicked(x, y); // Wait for any click
    out_p->ClearDrawArea();

    ///////////////////////////////////////////////////////////////////////////////////
    // TEST 4:
    //			Input Class : Check for the user action
    ///////////////////////////////////////////////////////////////////////////////////
    out_p->PrintMessage(
        "TEST4: Testing Input ability to detect User Action, click anywhere");

    ActionType ActType;
    gfxInfo.is_filled = false;
    /// TODO:
    // You must add a case for each action (both Draw mode and Play mode actions)
    // Add cases for the missing actions below
    do {
        ActType = in_p->GetUserAction();
        Point p1, p2, p3;
        gfxInfo.is_filled = false;
        switch (ActType) {
        case DRAW_RECT:
            out_p->PrintMessage("Action: Draw a CRectangle , Click anywhere");
            // Phase_2
            /*in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: Draw a CRectangle , Click anywhere else -_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawRect(p1 , p2 , gfxInfo , false);
			out_p->PrintMessage("Action: highlighting , click anywhere -_--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: highlighting , click anywhere else -_--_--_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawRect(p1 , p2 , gfxInfo , true);
			out_p->PrintMessage("Action: filling , click anywhere  -_--_--_--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: filling , click anywhere else -_____-");
			in_p->GetPointClicked(p2.x , p2.y);
			gfxInfo.is_filled = true;
			out_p->DrawRect(p1 , p2 , gfxInfo , false);
			out_p->PrintMessage("Action: filling highlighting , click anywhere -_____--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: filling highlighting , click anywhere else -_____--_--_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawRect(p1 , p2 , gfxInfo , true);*/
            break;

        case DRAW_LINE:
            out_p->PrintMessage("Action: Draw a Line , Click anywhere");
            // Phase_2
            /*in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: Draw a Line , Click anywhere else -_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawLine(p1 , p2 , gfxInfo , false);
			out_p->PrintMessage("Action: highlighting click anywhere -_--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: highlighting click anywhere else -_--_--_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawLine(p1 , p2 , gfxInfo , true);*/
            break;

        case DRAW_CIRC:
            out_p->PrintMessage("Action: Draw a Circle , Click anywhere");
            // Phase_2
            /*in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: Draw a Circle , Click anywhere else -_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawCircle(p1 , p2 , gfxInfo , false);
			out_p->PrintMessage("Action: highlighting , click anywhere -_--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: highlighting , click anywhere else -_--_--_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawCircle(p1 , p2 , gfxInfo , true);
			out_p->PrintMessage("Action: filling , click anywhere  -_--_--_--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: filling , click anywhere else -_____-");
			in_p->GetPointClicked(p2.x , p2.y);
			gfxInfo.is_filled = true;
			out_p->DrawCircle(p1 , p2 , gfxInfo , false);
			out_p->PrintMessage("Action: filling highlighting , click anywhere -_____--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: filling highlighting , click anywhere else -_____--_--_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->DrawCircle(p1 , p2 , gfxInfo , true);*/
            break;

        case DRAW_TRI:
            out_p->PrintMessage("Action: Draw a Triangle , Click anywhere");
            // Phase_2
            /*in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: Draw a Circle , Click anywhere else -_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->PrintMessage("Action: Draw a Circle , Click anywhere else -_--_-");
			in_p->GetPointClicked(p3.x , p3.y);
			out_p->DrawTriangle(p1 , p2 , p3 , gfxInfo , false);
			out_p->PrintMessage("Action: highlighting , click anywhere -_--_--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: highlighting , click anywhere else -_--_--_--_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->PrintMessage("Action: highlighting , click anywhere else -_____-");
			in_p->GetPointClicked(p3.x , p3.y);
			out_p->DrawTriangle(p1 , p2 , p3 , gfxInfo , true);
			out_p->PrintMessage("Action: filling , click anywhere  -_____--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: filling , click anywhere else -_____--_--_-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->PrintMessage("Action: filling , click anywhere else -_____--_--_--_-");
			in_p->GetPointClicked(p3.x , p3.y);
			gfxInfo.is_filled = true;
			out_p->DrawTriangle(p1 , p2 , p3 , gfxInfo , false);
			out_p->PrintMessage("Action: filling highlighting , click anywhere -_____--_--_--_--_-");
			in_p->GetPointClicked(p1.x , p1.y);
			out_p->PrintMessage("Action: filling highlighting , click anywhere else -__________-");
			in_p->GetPointClicked(p2.x , p2.y);
			out_p->PrintMessage("Action: filling highlighting , click anywhere else -__________--_-");
			in_p->GetPointClicked(p3.x , p3.y);
			out_p->DrawTriangle(p1 , p2 , p3 , gfxInfo , true);*/
            break;

        case CHNG_DRAW_CLR:
            out_p->PrintMessage("Action: Change the drawing color , Click anywhere");
            break;

        case CHNG_FILL_CLR:
            out_p->PrintMessage("Action: Change Fill color , Click anywhere");
            break;

        case CHNG_BK_CLR:
            out_p->PrintMessage("Action: Change Background color , Click anywhere");
            break;

        case DEL:
            out_p->PrintMessage("Action: Delete CFigure , Click anywhere");
            break;

        case MOVE:
            out_p->PrintMessage("Action: Move CFigure , Click anywhere");
            break;
        case SELECT:
            out_p->PrintMessage("Action: Select Figures , Click anywhere");
            break;

        case RESIZE:
            out_p->PrintMessage("Action: Resize Figures, Click anywhere");
            break;

        case ROTATE:
            out_p->PrintMessage("Action: Rotate The Figures , Click anywhere");
            break;

        case SEND_BACK:
            out_p->PrintMessage("Action: Send The CFigure Back , Click anywhere");
            break;

        case BRNG_FRNT:
            out_p->PrintMessage("Action: Bring The CFigure Front , Click anywhere");
            break;

        case SAVE:
            out_p->PrintMessage("Action: Save The CFigure , Click anywhere");
            break;

        case LOAD:
            out_p->PrintMessage("Action: Load CFigure , Click anywhere");
            break;

        case ZOOM_IN:
            out_p->PrintMessage("Action: Zoom In The Window , Click anywhere");
            break;
        case ZOOM_OUT:
            out_p->PrintMessage("Action: Zoom OUt The Window , Click anywhere");
            break;

        case CUT:
            out_p->PrintMessage("Action: Cut CFigure , Click anywhere");
            break;

        case COPY:
            out_p->PrintMessage("Action: Copy CFigure , Click anywhere");
            break;
        case PASTE:
            out_p->PrintMessage("Action: Paste The CFigure , Click anywhere");
            break;

        case STATUS:
            out_p->PrintMessage("Action: a click on the Status Bar, Click anywhere");
            break;

        case DRAWING_AREA:
            out_p->PrintMessage("Action: a click on the Drawing Area, Click anywhere");
            break;

        case EMPTY:
            out_p->PrintMessage("Action: a click on empty area in the Design Tool "
                                "Bar, Click anywhere");
            break;

        case TO_DRAW:
            out_p->PrintMessage(
                "Action: Switch to Draw Mode, creating simualtion tool bar");
            out_p->CreateDrawToolBar();
            break;

        case TO_PLAY:
            out_p->PrintMessage(
                "Action: Switch to Play Mode, creating Design tool bar");
            out_p->CreatePlayToolBar();
            break;
        case COLOR_BAR:
            out_p->PrintMessage("Action: a click on the Color Bar, Click anywhere");
            break;

        case EXIT:
            break;
        }
    } while (ActType != EXIT);

    /// Exiting
    out_p->PrintMessage("Action: EXIT, test is finished, click anywhere to exit");
    in_p->GetPointClicked(x, y);

    delete in_p;
    delete out_p;
    return 0;
}

#endif /* PHASE1 */