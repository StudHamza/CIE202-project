#pragma once


#include <vector>
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include <string>
using namespace std;

struct Point	//To be used for shapes points
{
	int x, y;
};

struct Box		//a two cordered rectangle for the hit box
{
	Point P1, P2;
};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr;	//Draw color of the shape
	color FillClr;	//Fill color of the shape
	color PrevClr;	//Pervious color before selection
	bool isFilled;	//shape Filled or not
	int BorderWdth;	//Width of shape borders
	bool isSelected;	//true if the shape is selected.
	bool isSaved;
};




class GUI
{
	enum GUI_MODE	//Graphical user interface mode
	{
		MODE_DRAW,	//Drawing mode (startup mode)
		MODE_PLAY	//Playing mode
	};

	enum DrawMenuIcon //The icons of the Draw menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_RECT,		//Recangle icon in menu
		ICON_CIRC,		//Circle icon in menu
		ICON_REGPOLY, //Regular polygon
		//TODO: Add more icons names here
		
		ICON_COLOR,
		ICON_PLAY,
		ICON_EXIT,		//Exit icon

		DRAW_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};
	enum VToolBarIcon //The icons displayed on the vertical tool bar
	{
		ICON_SELECT,
		ICON_DELETE,
		ICON_COPY,
		ICON_CLEAR,
		ICON_IMAGE,
		ICON_SAVE,
		ICON_LOAD,

		DRAW_ICON_COUNT_V
	};

	enum PlayMenuIcon //The icons of the Play menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here

		//TODO: Add more icons names here

		PLAY_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};




	GUI_MODE InterfaceMode;

	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		VToolBarImageH,		//Vertical toolbar heigtht
		VToolBarImageW,		//Width of 
		MenuIconWidth;		//Width of each icon in toolbar menu


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed



	window* pWind;
	window* pEWind;

public:

	GUI();

	// Input Functions  ---------------------------
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	string GetSrting(char c='c') const;	 //Returns a string entered by the user
	operationType GetUseroperation() const; //Read the user click and map to an operation

	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreateDrawVToolBar();
	void CreatePlayToolBar();	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void SetExit(window*);		//Creates window
	void DeleteExitWind();

	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	// -- shapes Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const;//Draw a rectangle
	void DrawRegPoly(Point P1, vector<int> Vx, vector<int> Vy,int s, GfxInfo RegPolyGfxInfo)const; //Draw a Regular polygon

	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg) const;	//Print a message on Status bar

	void PrintExitMessage(string msg,char p='u') const;	//Print a message on Exit window



	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width


	~GUI();
};

