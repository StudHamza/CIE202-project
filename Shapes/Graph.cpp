#include "Graph.h"
#include "../GUI/GUI.h"
#include <iostream>
#include <string>
#include "Load.h"
#include "Shape.h"
#include <typeinfo>


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
//						shapes Management Functions									//
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
	for (auto shapePointer : shapesList) {
		shapePointer->Draw(pUI);
	}
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
	selectedShape = selected;
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
				selectedShape = nullptr;
				return false;
			}
		}
	}
	else { return true; }
}


void Graph::Save(ofstream& file,color DrawClr,color FillClr,int BorderWidth) {
		if (file) {
			file << DrawClr.getClr() << "," << FillClr.getClr() << "," << BorderWidth << endl;
			file << shapesList.size()<<endl;
			for (auto& shape : shapesList) {
				shape->Save(file);
				shape->SetSaved(true);
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
		if (lineNum == 2) {
			//number of shapes
		}
		else if (getString(0, 2, line) == "Reg")
		{
			//Getting info from file
			Point P1, P2;		//rectangle corners
			int start, end, side, border; //start,end point   id,side and border Width
			color DrawClr, FillClr;		//Draw color fill color
			bool isFilled;
			border = line.back()-48;

			
			start = find(',', line, 2);		
			end = find(',', line, 3);
			side = stoi(getString(start+1, end, line));		//Number of side


			start = find('(', line);
			end = find(')', line);
			string c = getString(start, end, line);
			P1 = getP(c);								//Point 1


			start = find('(', line, 2);
			end = find(')', line, 2);
			string c2 = getString(start, end, line);
			P2 = getP(c2);							//Point 2


			start = find('(', line, 3);
			end = find(')', line, 3);
			DrawClr = Fcolor(getString(start, end, line));		//Draw color



			start = find('(', line, 4);
			end = find(')', line, 4);
			if (getString(start, end, line) != "(N)") {	//if fill
				FillClr = Fcolor(getString(start, end, line));	//Fill color	
				isFilled = true;
			}
			else
			{
				isFilled = false;			//is not filled
			}
			


			//Creating RegPoly
			GfxInfo RegPolyGfxInfo;
			RegPolyGfxInfo.BorderWdth = border;
			RegPolyGfxInfo.DrawClr = DrawClr;
			RegPolyGfxInfo.FillClr = FillClr;
			RegPolyGfxInfo.isFilled = isFilled;
			//Create a polygon with the above parameters

			RegPoly* R = new RegPoly(P1, P2, side, RegPolyGfxInfo);
			Addshape(R);
		}
		else if (getString(0, 2, line) == "Rec")
		{
			Point P1, P2;
			string holder;
			color DrawClr, FillClr;
			int start, end;
			bool isFilled;

			start = find('(', line);
			end = find(')', line);
			holder = getString(start, end, line);
			P1 = getP(holder);						//Point 1


			start = find('(', line, 2);
			end = find(')', line, 2);
			holder = getString(start, end, line);
			P2 = getP(holder);						//Point 2

			start = find('(', line, 3);
			end = find(')', line, 3);
			DrawClr = Fcolor(getString(start, end, line));		//Draw color


			start = find('(', line, 4);
			end = find(')', line, 4);
			if (getString(start,end,line) != "(N)") {	//if fill
				FillClr = Fcolor(getString(start, end, line));	//Fill color	
				isFilled = true;
			}
			else
			{
				isFilled = false;			//is not filled
			}



			//Constructing Rectangle
			//Creating th rectangle
			GfxInfo RectGfxInfo;
			RectGfxInfo.BorderWdth = border;
			RectGfxInfo.DrawClr = DrawClr;
			RectGfxInfo.FillClr = FillClr;
			RectGfxInfo.isFilled = isFilled;
			//Create a polygon with the above parameters
			Rect* R = new Rect(P1, P2, RectGfxInfo);
			Addshape(R);
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
		//cout << line << endl;
		lineNum++;
	}
}




void Graph::Clear() {
	for (auto& shape : shapesList) {
		delete shape;
	}
	shapesList.clear();
}

bool Graph::Exit()
{
	if (shapesList.size() > 0) {
		for (auto* shape : shapesList) {
			if ((shape->IsSaved()) == false) { return true; }
		}
	}
	return false;
}



void Graph::ClipBoard() {
	clipboard.clear();
	for (auto& selected : shapesList)
	{
		if (selected->IsSelected()) {
			selected->UnSelect();
			selectedShape = nullptr;
			clipboard.push_back(selected->Clone());	//problem: coppied item will have the same id
		}
	}
}

shape* Graph::GetSelectedShape()const
{
	return selectedShape;
}


void Graph::Paste() {
	//UnselectShape();	//unselect previous shape to select by defualt the copied
	const color pevClr = clipboard[0]->getPevDrawClr();
	for (auto& shape : clipboard) {
		
		shape->UpdateId();
		shape->Shift(10,10);
		shape->Selected(pevClr);
		Addshape(shape);
	}
	ClipBoard(); //updates the clipboard with new shapes

}


bool Graph::getClipBoard() const {
	if (clipboard.size() > 0)
		return true;
	else
		return false;
}