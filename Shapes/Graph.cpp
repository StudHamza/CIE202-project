#include "Graph.h"
#include "../GUI/GUI.h"
#include <iostream>
#include <string>
#include "Load.h"
#include "Shape.h"


Graph::Graph()
{
	selectedShape = nullptr;
}

Graph::~Graph()
{
	delete pvp;
	pvp = nullptr;
}

//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp)
{
	//Add a new shape to the shapes vector
	shapesList.push_back(pShp);
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (auto shapePointer : shapesList)
		shapePointer->Draw(pUI);
	pUI->CreateDrawToolBar(); //Prevents Shapes to flow into Tool bar
	pUI->CreateDrawVToolBar();
}



shape* Graph::Getshape(int x, int y) const
{
	//If a shape is found return a pointer to it.
	//if this point (x,y) does not belong to any shape return NULL
	for (auto& shapes : shapesList) {
		if (shapes->HitBox(x, y)) { return shapes; } //Q is the shapes here a pointer?
	}

	///Add your code here to search for a shape given a point x,y	
	return nullptr;
}

string Graph::SelectShape(Point P, color pevClr,shape *selected)
{

	*pvp = P; //Set previous point clicked

	selected->Selected(pevClr); //sets shape to selected
	return (selected->GetInfo('s')); //call select function that returns shape info as string

}
bool Graph::UnselectShape()
{
	if (!((*pvp).x==0 && (*pvp).y==0)) {  //checks if mouse is clicked after last unselect
		shape* pSelected = Getshape((*pvp).x, (*pvp).y);	//gets current selected shape
		if (pSelected) {
			if (pSelected->IsSelected()) {	//checks if bool select 
				pSelected->UnSelect();		//Unselects
				*pvp = { 0,0 };			//Resttore pev mouse click to nothing
				return false;
			}
		}
	}
	else { return true; }
}


void Graph::Save(ofstream& file,color DrawClr,color FillClr,int BorderWidth) {
		if (file) {
			file << DrawClr.getClr() << "," << FillClr.getClr() << "," << BorderWidth << endl;
			for (auto& shape : shapesList) {
				string line = shape->GetInfo('l');
				file << line << endl;
			}
		}
		file.close();
}

void Graph::load(ifstream& file) {
	string line;
	int border;
	int lineNum = 1;
	color GdrawClr, GfillClr;
	// Use a while loop together with the getline() function to read the file line by line
	while (getline(file, line))
	{
		if (lineNum == 1) //For first line Get Draw,Fill and Border Width
		{
			int start = find('(', line);
			int end = find(')', line);
			GdrawClr = Fcolor(getString(start, end, line));      //Draw color
			start = find('(', line, 2);
			end = find(')', line, 2);
			GfillClr = Fcolor(getString(start, end, line)); //Fill color
			border = line.back() - 48;             //Border Width
		}
		// Output the text from the file

		else if (getString(0, 2, line) == "Reg")
		{
			//Getting info from file
			Point corner1, corner2;		//rectangle corners
			int start, end,id,side,border;  //start,end point   id,side and border Width
			color DrawClr, FillClr;		//Draw color fill color
			border = line.back() - 48;
			id = line[find(',', line) + 1];
			side = line[find(',', line, 2) + 1];
			start = find('(', line);
			end = find(')', line);
			string c = getString(start, end, line);
			corner1 = getP(c);
			start = find('(', line, 2);
			end = find(')', line, 2);
			string c2 = getString(start, end, line);
			corner2 = getP(c2);
			start = find('(', line, 3);
			end = find(')', line, 3);
			DrawClr = Fcolor(getString(start, end, line));
			start = find('(', line, 4);
			end = find(')', line, 4);
			FillClr = Fcolor(getString(start, end, line));
			//Creating th rectangle
			GfxInfo RectGfxInfo;
			RectGfxInfo.BorderWdth = border;
			RectGfxInfo.DrawClr = DrawClr;
			RectGfxInfo.FillClr = FillClr;

			//Create a rectangle with the above parameters
			//Rect* R = new Rect(corner1, corner2, RectGfxInfo);

			//Add the rectangle to the list of shapes
			//Addshape(R);

		}
		else if (getString(0, 2, line) == "Rec")
		{
		}
		else if (getString(0, 2, line) == "Cir")
		{
		}
		else if (getString(0, 2, line) == "Tri")
		{
		}
		else if (getString(0, 2, line) == "Ova")
		{
		}
		else if (getString(0, 2, line) == "Irr")
		{
		}
		cout << line << endl;
		lineNum++;
		lineNum++;
	}
}


