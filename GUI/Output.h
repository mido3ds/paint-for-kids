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

    void CreateDrawToolBar() const; // creates Draw mode toolbar & menu
    void CreateFigItems() const;
    void CreateFigActions() const;
	void CreateBorderWidth() const;
	void CreateResize() const;

    void CreatePlayToolBar() const; // creates Play mode toolbar & menu
	void CreatePickBar() const;
	void CreateRestartGame() const;
	
	void CreateStatusBar() const;
	void CreateColorBar() const;

	void CreateDrawArea() const;
	void CreatePlayArea() const;

	void UpdateBuffer() const;

	Input* CreateInput() const; // creates a pointer to the Input object

    void ClearStatusBar(bool clear_msg=true);
    void ClearDrawArea() const;
    void ClearToolBar() const;
    void ClearTToolBar() const;

	// -- Figures Drawing functions
	void DrawRect(Point p1, Point p2, GfxInfo rect_gfx_info,
		bool selected) const;

	void DrawCircle(Point p1, int radius, GfxInfo circ_gfx_info,
		bool selected) const; // Draw a circle

	void DrawLine(Point p1, Point p2, GfxInfo line_gfx_info,
		bool selected) const; // Draw a line

	void DrawTriangle(Point p1, Point p2, Point p3, GfxInfo trngl_gfx_info,
		bool selected) const; // Draw a  tringle

	void PrintMessage(string msg, bool save_msg=false); // on Status bar

	color GetDrawColor() const;
	color GetFillColor() const;
	int GetPenWidth() const;
	int GetZoom() const; //Return zoom
	Point GetZoomPoint() const; //Return manager_zoom_point

	void SetZoom(int z);
	void SetZoomPoint(Point z_point);
	void SetDrawColor(color given_clr);
	void SetFillColor(color given_clr);
	void SetBkGrndColor(color given_clr);
	void SetPenWidth(int new_width);

private:
	window* wind_p; // Pointer to the Graphics Window

	Point TranslatePoint(const Point& p) const; // returns zoomed point
	int AdjustBorder(const int& border) const;
	int AdjustBorder15(const int& border) const;
	int AdjustBorder10(const int& border) const;
	int AdjustBorder3(const int& border) const;
	int AdjustBorder1(const int& border) const;
	int zoom = 0;
	Point zoom_point;

	string last_printed_msg;
};

#endif