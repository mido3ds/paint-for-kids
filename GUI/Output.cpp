#include "Output.h"

Output::Output()
{
    // Initialize user interface parameters
    UI.InterfaceMode = MODE_DRAW;

    UI.width = 1350;
    UI.height = 700;
    UI.wx = 5;
    UI.wy = 5;

    UI.StatusBarHeight = 50;
    UI.ToolBarHeight = 60;
    UI.colorBarWidth = 100;
    UI.colorBarHeight = 600;
    UI.MenuItemWidth = 60;

    UI.DrawColor = BLUE; // Drawing color						///
    // this Is Not Used
    UI.FillColor = GREEN; // Filling color
    UI.MsgColor = RED; // Messages color
    UI.BkGrndColor = WHITE; // Background color					/// I
    // Changed This [Back To Here To Customize The Tool Bar Background
    // Color]
    UI.HighlightColor = MAGENTA; // This color should NOT be used to draw figures.
    // use if for highlight only
    UI.StatusBarColor = TURQUOISE;
    UI.PenWidth = 3; // width of the figures frames			/// This Is Not Used
    // Also

    // Create the output window
    wind_p = CreateWindow(UI.width, UI.height, UI.wx, UI.wy);
    // Change the title
    wind_p->ChangeTitle("Paint for Kids - Programming Techniques Project");

    CreateDrawToolBar();
    CreateColorBar();
    CreateStatusBar();
}

Input* Output::CreateInput() const
{
    Input* in_p = new Input(wind_p);
    return in_p;
}

//======================================================================================//
//								Interface Functions
////
//======================================================================================//

window* Output::CreateWindow(int w, int h, int x, int y) const
{
    window* pW = new window(w, h, x, y);
    pW->SetBrush(UI.BkGrndColor);
    pW->SetPen(UI.BkGrndColor, 1);
    pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
    return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
    wind_p->SetPen(UI.StatusBarColor, 1);
    wind_p->SetBrush(UI.StatusBarColor);
    wind_p->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
    // Clear Status bar by drawing a filled white rectangle
    wind_p->SetPen(UI.StatusBarColor, 1);
    wind_p->SetBrush(UI.StatusBarColor);
    wind_p->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
    UI.InterfaceMode = MODE_DRAW;

    // You can draw the tool bar icons in any way you want.
    // Below is one possible way

    // First prepare List of images for each menu item
    // To control the order of these images in the menu,
    // reoder them in UI_Info.h ==> enum DrawMenuItem
    string MenuItemImages[DRAW_ITM_COUNT];
    MenuItemImages[ITM_LINE] = "images\\MenuItems\\line.jpg";
    MenuItemImages[ITM_RECT] = "images\\MenuItems\\rectangle.jpg";
    MenuItemImages[ITM_TRI] = "images\\MenuItems\\tringle.jpg";
    MenuItemImages[ITM_CIRC] = "images\\MenuItems\\circle.jpg";
    MenuItemImages[ITM_CHDC] = "images\\MenuItems\\draw-color.jpg";
    MenuItemImages[ITM_CHFC] = "images\\MenuItems\\fill-icon.jpg";
    MenuItemImages[ITM_CHBGC] = "images\\MenuItems\\background.jpg";
    MenuItemImages[ITM_DEL] = "images\\MenuItems\\delete_icon.jpg";
    MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move_icon.jpg";
    MenuItemImages[ITM_SELECT] = "images\\MenuItems\\select.jpg";
    MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\resize_icon.jpg";
    MenuItemImages[ITM_ROTATE] = "images\\MenuItems\\rotate_icon.jpg";
    MenuItemImages[ITM_SEND_BACK] = "images\\MenuItems\\up.jpg";
    MenuItemImages[ITM_BRING_FRONT] = "images\\MenuItems\\down.jpg";
    MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save.jpg";
    MenuItemImages[ITM_LOAD] = "images\\MenuItems\\open.jpg";
    MenuItemImages[ITM_ZOOM_IN] = "images\\MenuItems\\zoom_in.jpg";
    MenuItemImages[ITM_ZOOM_OUT] = "images\\MenuItems\\zoom_out.jpg";
    MenuItemImages[ITM_CUT] = "images\\MenuItems\\cut.jpg";
    MenuItemImages[ITM_COPY] = "images\\MenuItems\\copy.jpg";
    MenuItemImages[ITM_PASTE] = "images\\MenuItems\\paste.jpg";
    MenuItemImages[ITM_PLAY] = "images\\MenuItems\\play.jpg";
    MenuItemImages[ITM_EXIT] = "images\\MenuItems\\exit.jpg";

    // Draw menu item one image at a time
    for (int i = 0; i < DRAW_ITM_COUNT; i++)
        wind_p->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0,
            UI.MenuItemWidth, UI.ToolBarHeight);

    // Draw a line under the toolbar
    wind_p->SetPen(RED, 3);
    wind_p->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::CreateColorBar() const
{
    wind_p->DrawImage("images\\MenuItems\\coloring.jpg", 0, UI.ToolBarHeight,
        UI.colorBarWidth, UI.colorBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
    UI.InterfaceMode = MODE_PLAY;

    string MenuItemImages[PLAY_ITM_COUNT];
    MenuItemImages[ITM_PICK_HIDE] = "images\\MenuItems\\find.jpg";
    MenuItemImages[ITM_SCR_FIND] = "images\\MenuItems\\scramble.jpg";
    MenuItemImages[ITM_DRAW] = "images\\MenuItems\\draw.jpg";
    MenuItemImages[ITM_EXIT_PLAY] = "images\\MenuItems\\exit.jpg";

    // Draw menu item one image at a time
    for (int i = 0; i < DRAW_ITM_COUNT; i++)
        wind_p->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0,
            UI.MenuItemWidth, UI.ToolBarHeight);

    // Draw a line under the toolbar
    wind_p->SetPen(RED, 3);
    wind_p->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
    wind_p->SetPen(UI.BkGrndColor, 1);
    wind_p->SetBrush(UI.BkGrndColor);
    wind_p->DrawRectangle(UI.colorBarWidth, UI.ToolBarHeight, UI.width,
        UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const // Prints a message on status bar
{
    ClearStatusBar(); // First clear the status bar

    wind_p->SetPen(UI.MsgColor, 50);
    wind_p->SetFont(20, BOLD, BY_NAME, "Arial");
    wind_p->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.25), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::GetCrntDrawColor() const // get current drwawing color
{
    return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::GetCrntFillColor() const // get current filling color
{
    return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCrntPenWidth() const // get current pen width
{
    return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions
////
//======================================================================================//

void Output::DrawRect(Point p1, Point p2, GfxInfo rect_gfx_info,
    bool selected) const
{
    color DrawingClr;
    if (selected)
        DrawingClr = UI.HighlightColor; // Figure should be drawn highlighted
    else
        DrawingClr = rect_gfx_info.draw_clr;

    wind_p->SetPen(DrawingClr, rect_gfx_info.border_width); // Set Drawing color &
    // width

    drawstyle style;
    if (rect_gfx_info.is_filled) {
        style = FILLED;
        wind_p->SetBrush(rect_gfx_info.fill_clr);
    } else
        style = FRAME;

    wind_p->DrawRectangle(p1.x, p1.y, p2.x, p2.y, style);
}

void Output::DrawCircle(Point p1, Point p2, GfxInfo circ_gfx_info,
    bool selected) const
{
    int radius = sqrt(pow((p2.y - p1.y), 2) + pow((p2.x - p1.x), 2));
    color DrawingClr;
    if (selected)
        DrawingClr = UI.HighlightColor; // Figure should be drawn highlighted
    else
        DrawingClr = circ_gfx_info.draw_clr;

    wind_p->SetPen(DrawingClr, circ_gfx_info.border_width); // Set Drawing color &
    // width

    drawstyle style;
    if (circ_gfx_info.is_filled) {
        style = FILLED;
        wind_p->SetBrush(circ_gfx_info.fill_clr);
    } else
        style = FRAME;

    wind_p->DrawCircle(p1.x, p1.y, radius, style);
}

void Output::DrawLine(Point p1, Point p2, GfxInfo line_gfx_info,
    bool selected) const
{
    color DrawingClr;
    if (selected)
        DrawingClr = UI.HighlightColor; // Figure should be drawn highlighted
    else
        DrawingClr = line_gfx_info.draw_clr;

    wind_p->SetPen(DrawingClr, line_gfx_info.border_width); // Set Drawing color &
    // width

    drawstyle style = FRAME;

    wind_p->DrawLine(p1.x, p1.y, p2.x, p2.y, style);
}

void Output::DrawTriangle(Point p1, Point p2, Point p3, GfxInfo trngl_gfx_info,
    bool selected) const
{
    color DrawingClr;
    if (selected)
        DrawingClr = UI.HighlightColor; // Figure should be drawn highlighted
    else
        DrawingClr = trngl_gfx_info.draw_clr;

    wind_p->SetPen(DrawingClr, trngl_gfx_info.border_width); // Set Drawing color &
    // width

    drawstyle style;
    if (trngl_gfx_info.is_filled) {
        style = FILLED;
        wind_p->SetBrush(trngl_gfx_info.fill_clr);
    } else
        style = FRAME;

    wind_p->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, style);
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output() { delete wind_p; }
