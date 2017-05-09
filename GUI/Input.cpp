
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	wind_p = pW; // point to the passed window
}

clicktype Input::GetClickPoint(int& x, int& y) const
{
	clicktype click;
	click = wind_p->WaitMouseClick(x, y); // Wait for mouse click
	return click;
}

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1) {
		wind_p->WaitKeyPress(Key);
		if (Key == 27) // ESCAPE key is pressed
			return ""; // returns nothing as user has cancelled label
		if (Key == 13) // ENTER key is pressed
			return Label;
		if (Key == 8) // BackSpace is pressed
		{
			if (Label.size() != 0) // only resize it if label is not empty
				Label.resize(Label.size() - 1);
		}
		else
			Label += Key;
		pO->PrintMessage(Label);
	}
}

color Input::PickColor(int ix, int iy)
{
	if (ix < UI.TToolBarX && ix > UI.TToolBarY + UI.TToolBarWidth && iy < UI.TToolBarY && iy > UI.TToolBarY + UI.TToolBarHeight) {
		return WHITE;
	}
	return wind_p->GetColor(ix, iy);
}

// This function reads the position where the user clicks to determine the
// desired action
ActionType Input::GetUserAction()
{
    int x, y;
    wind_p->WaitMouseClick(x, y); // Get the coordinates of the user click
    last_click = { x, y };

    if (UI.InterfaceMode == MODE_DRAW) // GUI in the DRAW mode
    {
        //[1] If user clicks on the Toolbar
        if (y >= UI.ToolBarY && y < UI.ToolBarY + UI.ToolBarHeight) {
            // Check whick Menu item was clicked
            //==> This assumes that menu items are lined up horizontally <==
            int ClickedItemOrder = (x / UI.MenuItemWidth);
            // Divide x coord of the point clicked by the menu item width (int
            // division)
            // if division result is 0 ==> first item is clicked, if 1 ==> 2nd item
            // and so on

            switch (ClickedItemOrder) {
            case ITM_FIG:
                return DRAW_FIG_ITM;
            case ITM_EXIT:
                return EXIT;
            case ITM_CHBGC:
                return CHNG_BK_CLR;
            case ITM_SELECT:
                return SELECT;
			case ITM_DESELECT:
				return DESELECT;
            case ITM_CHDC:
                return CHNG_DRAW_CLR;
            case ITM_CHFC:
                return CHNG_FILL_CLR;
            case ITM_CTR:
                return CTR;
            case ITM_SAVE:
                return SAVE;
            case ITM_LOAD:
                return LOAD;
            case ITM_ZOOM_IN:
                return ZOOM_IN;
            case ITM_ZOOM_OUT:
                return ZOOM_OUT;
            case ITM_UNDO:
                return UNDO;
            case ITM_REDO:
                return REDO;
            case ITM_PLAY:
                return TO_PLAY;

            default:
                return EMPTY; // A click on empty place in desgin toolbar
            }
        }

        if (wind_p->isfigitems) {
            if (y >= UI.TToolBarY && y < UI.TToolBarY + UI.TToolBarHeight) {

                int ClickedItemOrder = (x / UI.MenuItemWidth);

                switch (ClickedItemOrder) {
                case ITM_LINE:
                    return DRAW_LINE;
                case ITM_RECT:
                    return DRAW_RECT;
                case ITM_TRI:
                    return DRAW_TRI;
                case ITM_CIRC:
                    return DRAW_CIRC;
                default:
                    return EMPTY;
                }
            }
        }
        if (wind_p->isfigactions) {
            if (y >= UI.TToolBarY && y < y < UI.TToolBarY + UI.TToolBarHeight) {

                int ClickedItemOrder = (x / UI.MenuItemWidth);

                switch (ClickedItemOrder) {
                case ITM_DEL:
                    return DEL;
                case ITM_MOVE:
                    return MOVE;
                case ITM_RESIZE:
                    return RESIZE;
                case ITM_ROTATE:
                    return ROTATE;
                case ITM_SEND_BACK:
                    return SEND_BACK;
                case ITM_BRING_FRONT:
                    return BRNG_FRNT;
                case ITM_CUT:
                    return CUT;
                case ITM_COPY:
                    return COPY;
                case ITM_PASTE:
                    return PASTE;
                default:
                    return EMPTY;
                }
            }
        }
        if (wind_p->iscolorbar) {
            if (y >= UI.TToolBarY && y < UI.TToolBarY + UI.TToolBarHeight) {
                return COLOR_BAR;
            }
        }

        //[2] User clicks on the drawing area
        if (y >= UI.DrawAreaY && y < UI.DrawAreaY + UI.DrawAreaHeight) {
            return DRAWING_AREA;
        }

        //[3] User clicks on the status bar
        return STATUS;
    } else // GUI is in PLAY mode
    {
        //[1] If user clicks on the Toolbar
        if (y >= 0 && y < UI.ToolBarHeight) {
            // Check whick Menu item was clicked
            //==> This assumes that menu items are lined up horizontally <==
            int ClickedItemOrder = (x / UI.MenuItemWidth);
            // Divide x coord of the point clicked by the menu item width (int
            // division)
            // if division result is 0 ==> first item is clicked, if 1 ==> 2nd item
            // and so on

            switch (ClickedItemOrder) {
            case ITM_PICK_HIDE:
                return HIDE;
            case ITM_SCR_FIND:
                return SCRAMBLE;
            case ITM_DRAW:
                return TO_DRAW;
            case ITM_EXIT_PLAY:
                return EXIT;
                
            default:
                return EMPTY; // A click on empty place in desgin toolbar
            }
        }
		if (wind_p->ispickbar) {
			if (y >= UI.TToolBarY && y < UI.TToolBarY + UI.TToolBarHeight) {

				int ClickedItemOrder = (x / UI.MenuItemWidth);

				switch (ClickedItemOrder) {
				case ITM_PICK_COLOR:
					return PICK_COLOR;
				case ITM_PICK_TYPE:
					return PICK_TYPE;
				case ITM_PICK_AREA:
					return PICK_AREA;
				case ITM_PICK_COL_TYP:
					return PICK_COL_TYP;
				default:
					return EMPTY;
				}
			}
		}

        //[2] User clicks on the drawing area
        if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight && x >= 0) {
            return DRAWING_AREA;
        }

        //[3] User clicks on the status bar
        return STATUS;
    }

}
/////////////////////////////////
Point Input::GetLastClickedPoint() const
{
    return last_click;
}
/////////////////////////////////

Input::~Input() {}

