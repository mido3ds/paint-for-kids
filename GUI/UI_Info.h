#ifndef UI_INFO_H
#define UI_INFO_H

#include "../CMUgraphicsLib/CMUgraphics.h"

// User Interface information file.
// This file contains info that is needed by Input and Output classes to
// handle the user interface

enum GUI_MODE // Graphical user interface mode
{
    MODE_DRAW, // Drawing mode (startup mode)
    MODE_PLAY // Playing mode
};

enum DrawMenuItem // The items of the Draw menu (you should add more items)
{
    // Note: Items are ordered here as they appear in menu
    // If you want to change the menu items order, change the order here
    ITM_LINE, // Line
    ITM_RECT, // Recangle item in menu
    ITM_TRI, // Triangle
    ITM_CIRC, // Circle item in menu
    ITM_CHDC, // Change Draw Color
    ITM_CHFC, // Change Fill Color
    ITM_CHBGC, // change Background Item
    ITM_DEL, // Delete
    ITM_MOVE, // Move
    ITM_SELECT,
    ITM_RESIZE, // Resize
    ITM_ROTATE, // Rotate
    ITM_SEND_BACK, // Send Back
    ITM_BRING_FRONT, // Bring Front
    ITM_SAVE, // Save
    ITM_LOAD, // Load File
    ITM_ZOOM_IN,
    ITM_ZOOM_OUT,
    ITM_CUT,
    ITM_COPY,
    ITM_PASTE,
    ITM_PLAY,

    ITM_EXIT, // Exit item

    DRAW_ITM_COUNT // no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem // The items of the Play menu (you should add more items)
{
    // Note: Items are ordered here as they appear in menu
    // If you want to change the menu items order, change the order here
    ITM_PICK_HIDE,
    ITM_SCR_FIND,
    ITM_DRAW,
    ITM_EXIT_PLAY,

    PLAY_ITM_COUNT // no. of menu items ==> This should be the last line in this enum

};

// This line to prevent "redefinition error"
__declspec(selectany)

    struct UI_Info // User Interface Info.
{
    GUI_MODE InterfaceMode;

    int width, height, // Window width and height
        wx, wy, // Window starting coordinates
        StatusBarHeight, // Status Bar Height
        ToolBarHeight, // Tool Bar Height (distance from top of window to bottom
        // line of toolbar)
        MenuItemWidth, // Width of each item in toolbar menu
        colorBarWidth, // Color Bar Width
        colorBarHeight, // Color Bar height
        playAreaWidthone,
        playAreaWidthtwo,
        playAreaHeight;

    color DrawColor; // Drawing color
    color FillColor; // Filling color
    color HighlightColor; // Highlighting color
    color MsgColor; // Messages color
    color BkGrndColor; // Background color
    color StatusBarColor; // Status bar color
    int PenWidth; // width of the pen that draws shapes

    /// Add more members if needed

} UI; // create a global object UI

#endif