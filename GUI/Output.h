#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output // The application manager should have a pointer to this class
{
public:
    Output();
    ~Output();

    window* CreateWindow(int, int, int, int) const; // main window

    void CreateDrawToolBar() const; // creates Draw mode toolbar & menu
    void CreatePlayToolBar() const; // creates Play mode toolbar & menu

    void CreateStatusBar() const;
    void CreateColorBar() const;

    Input* CreateInput() const; // creates a pointer to the Input object

    void ClearStatusBar() const;
    void ClearDrawArea() const;

    // -- Figures Drawing functions
    void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo,
        bool selected = false) const; // Draw a rectangle

    void DrewCir(Point P1, Point P2, GfxInfo RectGfxInfo,
        bool selected) const; // Draw a circle

    void DrewLin(Point p1, Point p2, GfxInfo RectGfxInfo,
        bool selected) const; // Draw a line

    void DrewTrig(Point p1, Point p2, Point p3, GfxInfo RectGfxInfo,
        bool selected) const; // Draw a  tringle

    /// TODO: Make similar functions for drawing all other figures.

    void PrintMessage(string msg) const; // on Status bar

    color GetCrntDrawColor() const;
    color GetCrntFillColor() const;
    int GetCrntPenWidth() const;

private:
    window* wind_p; // Pointer to the Graphics Window
};

#endif