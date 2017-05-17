#include "Input.h"
#include "Output.h"


Input::Input(window* pW)
{
	wind_p = pW; // point to the passed window
}

clicktype Input::GetClick(int& x, int& y) const
{
    clicktype clk_type;
    while ((clk_type = wind_p->GetMouseClick(x, y)) == clicktype::NO_CLICK);
    return clk_type;
}

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
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

color Input::GetColor(int ix, int iy)
{
	if (ix < UI.TToolBarX && ix > UI.TToolBarY + UI.TToolBarWidth && iy < UI.TToolBarY && iy > UI.TToolBarY + UI.TToolBarHeight) 
		return WHITE;
	
	return wind_p->GetColor(ix, iy);
}

// from click point, return the desired action
ActionType Input::GetUserAction()
{

	/*int time = 0;
	bool loop = false;
	bool exit = true;
	while (exit)
	{
		if (loop == false)
		{
			if (wind_p->GetButtonState(LEFT_BUTTON, last_click.x, last_click.y) == BUTTON_DOWN)
			{
				if ((last_click.y <= UI.ToolBarHeight) || (last_click.x <= UI.TToolBarWidth && last_click.y <= (UI.TToolBarWidth + UI.MenuItemHeight) && last_click.y >= UI.MenuItemHeight))
					break;
				loop = true;
			}
		}
		else
		{
			if (wind_p->GetButtonState(LEFT_BUTTON, last_click.x, last_click.y) == BUTTON_UP)
			{
				loop = false;
				exit = false;
			}
			else
			{
				cout << "not yet" << endl;
				if (time == 1500000)
				{ cout << "Drag" << endl; }
				time++;
			}
		}
	}*/

	while (GetClick(last_click.x, last_click.y) != clicktype::LEFT_CLICK);
	int x = last_click.x, y = last_click.y;

	if (UI.InterfaceMode == MODE_DRAW) // GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (last_click.y >= UI.ToolBarY && last_click.y < UI.ToolBarY + UI.ToolBarHeight) {
			// Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (last_click.x / UI.MenuItemWidth);
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
			if (last_click.y >= UI.TToolBarY && last_click.y < UI.TToolBarY + UI.TToolBarHeight) {

				int ClickedItemOrder = (last_click.x / UI.MenuItemWidth);

				switch (ClickedItemOrder)
				{
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
			if (last_click.y >= UI.TToolBarY && last_click.y < UI.TToolBarY + UI.TToolBarHeight) {

				int ClickedItemOrder = (last_click.x / UI.MenuItemWidth);

				switch (ClickedItemOrder)
				{
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
			if (last_click.y >= UI.TToolBarY && last_click.y < UI.TToolBarY + UI.TToolBarHeight) {
				return COLOR_BAR;
			}
		}

		//[2] User clicks on the drawing area
		if (last_click.y >= UI.DrawAreaY && last_click.y < UI.DrawAreaY + UI.DrawAreaHeight)
			return DRAWING_AREA;

		//[3] User clicks on the status bar
		return STATUS;
	}
	else // GUI is in PLAY mode
	{
		//[1] If user clicks on the Toolbar
		if (last_click.y >= 0 && last_click.y < UI.ToolBarHeight) {
			// Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (last_click.x / UI.MenuItemWidth);
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
			if (last_click.y >= UI.TToolBarY && last_click.y < UI.TToolBarY + UI.TToolBarHeight) {

				int ClickedItemOrder = (last_click.x / UI.MenuItemWidth);

				switch (ClickedItemOrder)
				{
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

		//[3] User clicks on the status bar
		return STATUS;
	}

}
/////////////////////////////////
bool Input::IsMouseDown(button btn_state,int &x,int &y) const
{
    
    return wind_p->GetButtonState(btn_state, x, y) == BUTTON_DOWN;
}

clicktype Input::WaitMouseClick(int & iX, int & iY)
{
	return wind_p->WaitMouseClick(iX, iY);
}

/////////////////////////////////
Point Input::GetMouseCoord() const
{
    int x, y;
    wind_p->GetMouseCoord(x, y);
    return {x, y};
}
/////////////////////////////////
Point Input::GetLastClickedPoint() const
{
    return last_click;
}
/////////////////////////////////
Input::~Input() {}