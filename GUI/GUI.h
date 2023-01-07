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
	vector<color>PevDrawColors;
	vector<color>PevFillColors;
	vector<bool>FillHistory;
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
		ICON_LINE,
		ICON_RECT,		//Recangle icon in menu
		ICON_CIRC,		//Circle icon in menu
		ICON_OVAL,
		ICON_TRI,
		ICON_REGPOLY, //Regular polygon
		//TODO: Add more icons names here
		
		ICON_PEN,
		ICON_FILL,

		ICON_COLOR,
		ICON_UNDO,
		ICON_REDO,
		ICON_SCRAMBLE,
		ICON_MULTIMOVE,
		ICON_PLAY,
	
		ICON_EXIT,		//Exit icon

		DRAW_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};
	enum VToolBarIcon //The icons displayed on the vertical tool bar
	{
		ICON_SELECT,
		ICON_DRAG,
		ICON_DELETE,
		ICON_COPY,
		ICON_PASTE,
		ICON_CLEAR,
		ICON_CUT,
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
		MenuIconWidth,		//Width of each icon in toolbar menu
		VToolStart;			//Starting point of vertical tool bar


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	char SelectedCrntColor;


	window* pWind;
	window* pEWind;

public:

	GUI();

	// Input Functions  ---------------------------
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	buttonstate GetButtonState(button, int&, int&);
	string GetSrting(char c='c') const;	 //Returns a string entered by the user
	bool GetKeyClicked()const;		//Return key modifiers
	operationType GetUseroperation() const; //Read the user click and map to an operation

	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreateDrawVToolBar();
	void CreatePlayToolBar();	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void SetExit(window*);		//Creates window
	void DeleteExitWind();
	void updatebuffer();

	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	// -- shapes Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const;//Draw a rectangle
	void DrawRegPoly(Point P1, vector<int> Vx, vector<int> Vy,int s, GfxInfo RegPolyGfxInfo)const; //Draw a Regular polygon
	void DrawCircle(Point P1, int Radius, GfxInfo CircleGfxInfo)const;
	void DrawTriangle(Point, Point, Point, GfxInfo)const;	//Draw Triangle
	void DrawOval(Point, Point, GfxInfo)const;
	void DrawLine(Point, Point,GfxInfo)const;	//Draw a line

	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg) const;	//Print a message on Status bar

	void PrintExitMessage(string msg,char p='u') const;	//Print a message on Exit window

	//Frame Image
	void FrameImage(image,int,int);
	void DrawImage(string, Point, Point);

	//Colors
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	///////
	color getColor(Point)const;		//Gets color from exact coordinates
	//////
	void setCrntSelectedColor(char);	//Set border color to selected
	char getCrntSelectedColor()const;	//gets state of selected color

	void ChangeDrawColor(color);
	void ChangeFillColor(color);


	//Keyboard events

	~GUI();
};

