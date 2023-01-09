#include "GUI.h"
#include "vector"

#include<iostream>
GUI::GUI()
{
	//Initialize user interface parameters
	InterfaceMode = MODE_DRAW;

	width = 1500;
	height = 800;
	wx = 5;
	wy = 5;


	StatusBarHeight = 50;
	ToolBarHeight = 50;
	VToolBarImageW = 50;
	VToolBarImageH = 50;
	MenuIconWidth = 70;
	VToolStart = 150;

	DrawColor = BLUE;	//default Drawing color
	FillColor = GREEN;	//default Filling color
	MsgColor = BLACK;		//Messages color
	BkGrndColor = WHITE;	//Background color
	StatusBarColor = BLUEVIOLET;
	PenWidth = 3;	//default width of the shapes frames
	SelectedCrntColor = 'd';


	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");

	CreateDrawToolBar();
	CreateStatusBar();
	CreateDrawVToolBar();

	







}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}


buttonstate GUI::GetButtonState(button b, int& x, int& y) {                           //added


	return(pWind->GetButtonState(b, x, y));

}

bool GUI::GetKeyClicked()const
{
	if (GetKeyState(VK_SHIFT) & 0x8000)
		return true;
	return false;
}

string GUI::GetSrting(char c) const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		if (c == 'c')
			ktype = pWind->WaitKeyPress(Key);
		else
			ktype = pEWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else {
			Label += Key;
		}
		if (c == 'c')
			PrintMessage(Label);
		else
			PrintExitMessage(Label, 'd');
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	if (InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{

		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check which Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / (MenuIconWidth));
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case ICON_LINE: return DRAW_LINE;
			case ICON_RECT: return DRAW_RECT;
			case ICON_CIRC: return DRAW_CIRC;
			case ICON_OVAL: return DRAW_OVAL;
			case ICON_TRI:	return DRAW_TRI;
			case ICON_REGPOLY: return DRAW_REGPOLY;
			case ICON_IREGPOLY:return DRAW_IREG;
			case ICON_PEN: return CHNG_DRAW_CLR;
			case ICON_FILL: return CHNG_FILL_CLR;
			case ICON_COLOR: return COLOR_PALETTE;
			case ICON_UNDO: return UNDO;
			case ICON_REDO: return REDO;
			case ICON_SCRAMBLE:return SCRAMBLE;
			case ICON_RESIZE:return RESIZE;
			case ICON_PLAY: return TO_PLAY;
			case ICON_EXIT: return EXIT;
			case ICON_MULTIMOVE:return MULTIMOVE;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}
		//[4] user clicks on vertical tool bar
		if (x >= 0 && x <= VToolBarImageW && y>=VToolStart)
		{
			int ClickedIconOrderV = ((y-VToolStart) / (VToolBarImageH));

			switch (ClickedIconOrderV)
			{
			case ICON_SELECT: return SELECT_SHAPE;
			case ICON_DRAG:return DRAG;
			case ICON_Resize_by_Drag:return Resize_by_DRAG;
			case ICON_DELETE:  return DEL;
			case ICON_COPY: return COPY;
			case ICON_PASTE: return PASTE;
			case ICON_CLEAR: return CLEAR;
			case ICON_CUT: return CUT;
			case ICON_IMAGE: return POST_IMAGE;
			case ICON_SAVE:  return SAVE ;
			case ICON_LOAD: return LOAD;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[3] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[4] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding operation
		return TO_PLAY;	//just for now. This should be updated
	}

}
////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);
	return pW;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::SetExit(window*pE) {
	pE->ChangeTitle("Paint and Play");
	pEWind = pE;
}
/////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);

	
	




}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);

}
////////////////////////////////////////////

void GUI::updatebuffer() {


	pWind->UpdateBuffer();


}



//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() 
{
	InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu icon
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuIcon
	string MenuIconImages[DRAW_ICON_COUNT];
	MenuIconImages[ICON_LINE]="images\\MenuIcons\\Menu_Line.jpg";
	MenuIconImages[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_CIRC] = "images\\MenuIcons\\Menu_Circ.jpg";
	MenuIconImages[ICON_OVAL] = "images\\MenuIcons\\Menu_Oval.jpg";
	MenuIconImages[ICON_TRI] = "images\\MenuIcons\\Menu_Triangle.jpg";
	MenuIconImages[ICON_REGPOLY] = "images\\MenuIcons\\Menu_RegPoly.jpg";
	MenuIconImages[ICON_IREGPOLY] = "images\\MenuIcons\\Menu_IregPoly.jpg";
	MenuIconImages[ICON_PEN] = "No_image";
	MenuIconImages[ICON_FILL] = "No_Image";
	MenuIconImages[ICON_COLOR]="images\\MenuIcons\\Menu_Color.jpg";
	MenuIconImages[ICON_UNDO]="images\\MenuIcons\\Menu_Undo.jpg";
	MenuIconImages[ICON_REDO]="images\\MenuIcons\\Menu_Redo.jpg";
	MenuIconImages[ICON_RESIZE] = "images\\MenuIcons\\Menu_RESIZE.jpg";
	
	MenuIconImages[ICON_PLAY] = "images\\MenuIcons\\Menu_Play.jpg";
	MenuIconImages[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";
	MenuIconImages[ICON_SCRAMBLE] = "images\\MenuIcons\\Menu_SCRAMBLE.jpg";
	MenuIconImages[ICON_MULTIMOVE] = "images\\MenuIcons\\Menu_MULTIMOVE.jpg";

	//TODO: Prepare images for each menu icon and add it to the list
	
	//Draw menu icon one image at a time
	for (int i = 0; i < DRAW_ICON_COUNT; i++) {
		pWind->SetPen(DARKRED, 4);
		pWind->DrawLine(MenuIconWidth * (i+1), 0, (i+1) * MenuIconWidth, ToolBarHeight);
		if (i != ICON_PEN && i!=ICON_FILL) {
			pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth - 5, ToolBarHeight);
		}
		else {
			string msg;
			if (i == ICON_PEN) {
				msg = "Pen Color";
				pWind->SetBrush(DrawColor);
			}
			else if (i == ICON_FILL)
			{
				msg = "Fill Color";
				pWind->SetBrush(FillColor);
			}
			pWind->SetFont(16, BOLD, BY_NAME, "Arial");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(MenuIconWidth * (i)+4, ToolBarHeight - 15, msg);//Nubers represents padding
			pWind->DrawRectangle(MenuIconWidth * (i)+10, 5, (i + 1) * MenuIconWidth-10, ToolBarHeight-15);//10 represents the padding
		}
	}

	//Draw a line under the toolbar
	pWind->SetPen(DARKRED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}

void GUI::CreatePlayToolBar() 
{
	InterfaceMode = MODE_PLAY;
	string MenuIconImages[PLAY_ICON_COUNT];
		MenuIconImages[ICON_START] = "images\\MenuIcons\\Menu_START.jpg";
	MenuIconImages[ICON_RESTART] = "images\\MenuIcons\\Menu_RESTART.jpg";

	MenuIconImages[ICON_HIDE] = "images\\MenuIcons\\Menu_Hide.jpg";
	MenuIconImages[ICON_UNHIDE] = "images\\MenuIcons\\menu_unhide.jpg";

	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////
//                  CREATING THE VERTICLE TOOL BAR                                     	//
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawVToolBar() {
	string VToolBarIcon[DRAW_ICON_COUNT_V];
	VToolBarIcon[ICON_SELECT] = "images\\VToolBar\\Select_Icon.jpg";
	VToolBarIcon[ICON_DRAG]= "images\\VToolBar\\DRAG_Icon.jpg";
	VToolBarIcon[ICON_Resize_by_Drag] = "images\\VToolBar\\ResizebyDrag_Icon.jpg";
	VToolBarIcon[ICON_DELETE] = "images\\VToolBar\\Delete_Icon.jpg";
	VToolBarIcon[ICON_COPY] = "images\\VToolBar\\Copy_Icon.jpg";
	VToolBarIcon[ICON_PASTE] = "images\\VToolBar\\Paste_Icon.jpg";
	VToolBarIcon[ICON_CLEAR] = "images\\VToolBar\\Clear_Icon.jpg";
	VToolBarIcon[ICON_CUT] = "images\\VToolBar\\Cut_Icon.jpg";
	VToolBarIcon[ICON_IMAGE] = "images\\VToolBar\\Image_Icon.jpg";
	VToolBarIcon[ICON_SAVE] = "images\\VToolBar\\Save_Icon.jpg";
	VToolBarIcon[ICON_LOAD] = "images\\VToolBar\\Load_Icon.jpg";
	
	//DRAW MENUE
	for (int i = 0; i < DRAW_ICON_COUNT_V; i++) {
		pWind->SetPen(DARKRED, 4);
		pWind->DrawImage(VToolBarIcon[i], 0, (VToolBarImageH * i) + VToolStart, VToolBarImageW, VToolBarImageH-5);
		pWind->DrawLine(0, (VToolBarImageH * (i+1)) + VToolStart, VToolBarImageW, (VToolBarImageH * (i+1)) + VToolStart);
	}

	pWind->DrawLine(VToolBarImageW, ToolBarHeight, VToolBarImageW, 650);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(VToolBarImageW, ToolBarHeight, width-VToolBarImageW, height - StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}

void GUI::PrintExitMessage(string msg,char p) const	//Prints a message on status bar
{	
	pEWind->SetPen(WHITE, 1);
	pEWind->SetBrush(WHITE);
	pEWind->DrawRectangle(10, 70,	pEWind->GetWidth(), pEWind->GetHeight());
	pEWind->SetPen(RED, 50);
	pEWind->SetFont(24, BOLD, BY_NAME, "Arial");
	if (p == 'u')
	{
		pEWind->DrawString(10, 50, msg);
	}
	else{ pEWind->DrawString(10, 70, msg); }
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ChangeDrawColor(color draw_color)
{
	DrawColor = draw_color;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ChangeFillColor(color fill_color)
{
	FillColor = fill_color;
}


//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getColor(Point mouse)const
{
	color Chosen;
	Chosen =pWind->GetColor(mouse.x, mouse.y);
	return Chosen;
}


//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntSelectedColor(char s)
{
	SelectedCrntColor = s;	//d or f: representing draw or fill
}

char GUI::getCrntSelectedColor()const
{
	return SelectedCrntColor;
}
/////////////////////////////////////////////////////////////////////////////////////////




int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;

	DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);


	cout << pWind->GetWidth() << endl;
	cout << pWind->GetHeight() << endl;


	
}


void GUI::DrawRegPoly(Point P1,  vector<int> Xv, vector<int> Yv,int side, GfxInfo RegPolyGfxInfo)const
{
	color DrawingClr;

	DrawingClr = RegPolyGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RegPolyGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RegPolyGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RegPolyGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int *x=&Xv[0];
	int* y = &Yv[0];
	pWind->DrawPolygon(x,y,side,style);
}



void GUI::DrawCircle(Point P1,int Radius,GfxInfo CircleGfxInfo)const
{
	color DrawingClr;

	DrawingClr = CircleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircleGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawCircle(P1.x, P1.y, Radius, style);
}



void GUI::DrawTriangle(Point P1, Point P2,Point P3 ,GfxInfo TriangleGfxInfo) const
{
	color DrawingClr;

	DrawingClr = TriangleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriangleGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriangleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriangleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y,P3.x,P3.y ,style);


}


void GUI::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo)const
{
	color DrawingClr;

	DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (LineGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(LineGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawLine(P1.x,P1.y,P2.x,P2.y,style);
}





void GUI::DrawOval(Point P1, Point P2, GfxInfo OvalGfxInfo) const
{
	color DrawingClr;

	DrawingClr = OvalGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, OvalGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (OvalGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(OvalGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawEllipse(P1.x,P1.y,P2.x,P2.y,style);

}


void GUI::DrawIREG(int n, int* array_ofxs, int* array_ofys, GfxInfo IREGPolGfxInfo) const {
	color DrawingClr;
	if (IREGPolGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = IREGPolGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, IREGPolGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (IREGPolGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(IREGPolGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawPolygon(array_ofxs, array_ofys,n, style);




}

/////////////////////////////////////////////////////////////////////////////////\

void GUI::FrameImage(image stick,int x,int y)
{
	SetPixel(stick.getHDC(), x, y, (255, 255, 255));
}

void GUI::DrawImage(string Image, Point P1, Point P2)
{
	
	pWind->DrawImage(Image, P1.x, P1.y, P2.x, P2.y);
}
void GUI::DrawImage(string Image, int x1,int y1,int x2, int y2)
{
	pWind->DrawImage(Image, x1, y1, x2, y2);
}



void GUI::DeleteExitWind()
{
	delete pEWind;
}



//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

