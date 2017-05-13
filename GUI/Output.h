#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"
#include <cmath>
#include <iostream> // cerr

class Output // The application manager should have a pointer to this class
{
public:
	Output();
	~Output();

	window* CreateWind(int, int, int, int) const; // main window
	Input* CreateInput() const; // creates a pointer to the Input object

	// -- Draw Area
	void CreateDrawArea() const;
    void ClearDrawArea() const;

	// -- Create Toolbars
    void CreateDrawToolBar() const; // creates Draw mode toolbar & menu
    void CreatePlayToolBar() const; // creates Play mode toolbar & menu

    void CreateFigItems() const;
    void CreateFigActions() const;
	void CreateBorderToolbar() const;
	void CreatePickBar() const;
	void CreateRestartGame() const;
	void CreateColorBar() const;

	// -- Clear Toolbars
    void ClearStatusBar(bool clear_msg = true) const;
    void ClearToolbar() const;
    void ClearTempToolbar() const;

	// -- Draw Figures
	void DrawRect(Point p1, Point p2, GfxInfo rect_gfx_info, bool selected) const;
	void DrawCircle(Point p1, int radius, GfxInfo circ_gfx_info, bool selected) const;
	void DrawLine(Point p1, Point p2, GfxInfo line_gfx_info, bool selected) const;
	void DrawTriangle(Point p1, Point p2, Point p3, GfxInfo trngl_gfx_info, bool selected) const;

	void PrintMessage(string msg, color msgc = WHITE, bool save_msg = false) const; // on Status bar

	color GetDrawColor() const;
	color GetFillColor() const;
	int GetPenWidth() const;
	int GetZoomScale() const; //Return zoom scale ..., -2, -1, 0, 1, 2, 3, ...
	Point GetZoomPoint() const; //Return manager_zoom_point

	void SetZoomScale(int z);
	void SetZoomPoint(Point z_point);
	void SetDrawColor(color given_clr);
	void SetFillColor(color given_clr);
	void SetBkGrndColor(color given_clr);
	void SetPenWidth(int new_width);

private:
	window* wind_p; // Pointer to the Graphics Window

	Point TranslatePoint(const Point&) const; // returns zoomed point
	int AdjustBorder(const int& border) const;
	int AdjustBorder15(const int& border) const;
	int AdjustBorder10(const int& border) const;
	int AdjustBorder3(const int& border) const;
	int AdjustBorder1(const int& border) const;
	int zoom_scale = 0;
	Point zoom_point;

	string last_printed_msg;
};

#endif