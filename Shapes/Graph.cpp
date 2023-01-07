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



///////////////////MULTIMOVE FUNCTIONS

void Graph:: getshapeslimitsX(int& xMA,int& xMI) {                   //useed in multimove
	int xmax = 0, xmin = 0;
int x1=0, x2=0;
int T1=0, T2=3000;           // limits that cant be exceeded whether in max or min(ised as a memoery to get the max/min for all selected shapes)


	for(unsigned i=0;i< shapesList.size();i++)
		if (shapesList[i]->IsSelected()) {
			
			 shapesList[i]->getXlimits(x1,x2);
			xmax = max(x1, T1);
			xmin = min(x2, T2);
			T1 = x1;
			T2 = x2;
		}
			
xMA=	xmax  ;
		 
  xMI=  xmin;




}



void Graph:: getshapeslimitsY(int& yMA,int& yMI){                                  //used in multimove
	int ymax = 0, ymin = 0;
	int y1=0, y2=0;
	int T1 = 0, T2 = 3000;// limits that cant be exceeded whether in max or min(ised as a memoery to get the max/min for all selected shapes)

	for (unsigned i = 0; i < shapesList.size(); i++)
		if (shapesList[i]->IsSelected()) {

			 shapesList[i]->getYlimits(y1,y2);
			ymax = max(y1, T1);
			ymin = min(y2, T2);
			T1 = y1;
			T2 = y2;
		}

	yMA = ymax;
		 
		 
	yMI=ymin;
	
	
	
	
};


void Graph::multimove(int x1,int y1,int x2, int y2) {

	for (unsigned i = 0; i < shapesList.size(); i++)
		if (shapesList[i]->IsSelected()) {
			shapesList[i]->relative_move(x1, y1, x2, y2);
			shapesList[i]->UnSelect();


		}



}










/////////////////////////////////////

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

void Graph::random_move() {
	srand(time(0));
	for (unsigned i = 0; i < shapesList.size(); i++) {
		int x = rand() % (1130) + 100;
		int y = rand() % (501) + 95;


		shapesList[i]->Move(x, y);

	}
}

string Graph::SelectShape(Point P, color pevClr,shape *selected)
{
	selectedShape = nullptr;
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
				UnSelectAll();
				*pvp = { 0,0 };			//Resttore pev mouse click to nothing
				selectedShape = nullptr;
				return false;
			}
		}
	}
	else { return true; }
}


void Graph::UnSelectAll()
{
	for (shape* selected_shapes : shapesList)
	{
		if(selected_shapes->IsSelected())
			selected_shapes->UnSelect();
	}
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
			int start, end,Sborder;
			bool isFilled;


			Sborder = line.back() - 48;		//Border

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
			RectGfxInfo.BorderWdth = Sborder;
			RectGfxInfo.DrawClr = DrawClr;
			RectGfxInfo.FillClr = FillClr;
			RectGfxInfo.isFilled = isFilled;
			//Create a polygon with the above parameters
			Rect* R = new Rect(P1, P2, RectGfxInfo);
			Addshape(R);
		}
		else if (getString(0, 2, line) == "Cir")
		{
		Point P1, P2;
		string holder;
		color DrawClr, FillClr;
		int start, end,Sborder;
		bool isFilled;

		Sborder = line.back() - 48;		//Circle border

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
		if (getString(start, end, line) != "(N)") {	//if fill
			FillClr = Fcolor(getString(start, end, line));	//Fill color	
			isFilled = true;
		}
		else
		{
			isFilled = false;			//is not filled
		}



		//Constructing Circle
		//Intialzing Gfx infp
		GfxInfo CircleGfxInfo;
		CircleGfxInfo.BorderWdth = Sborder;
		CircleGfxInfo.DrawClr = DrawClr;
		CircleGfxInfo.FillClr = FillClr;
		CircleGfxInfo.isFilled = isFilled;
		//Create a polygon with the above parameters
		Circle* C = new Circle(P1, P2, CircleGfxInfo);
		Addshape(C);
		}
		else if (getString(0, 2, line) == "Tri")
		{
		//Getting info from file
		Point P1, P2,P3;		//rectangle corners
		int start, end, side, border; //start,end point   id,side and border Width
		color DrawClr, FillClr;		//Draw color fill color
		bool isFilled;
		border = line.back() - 48;


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
		string c3 = getString(start, end, line);
		P3 = getP(c3);							//Point 3


		start = find('(', line, 4);
		end = find(')', line, 4);
		DrawClr = Fcolor(getString(start, end, line));		//Draw color



		start = find('(', line, 5);
		end = find(')', line, 5);
		if (getString(start, end, line) != "(N)") {	//if fill
			FillClr = Fcolor(getString(start, end, line));	//Fill color	
			isFilled = true;
		}
		else
		{
			isFilled = false;			//is not filled
		}



		//Creating RegPoly
		GfxInfo TriangleGfxInfo;
		TriangleGfxInfo.BorderWdth = border;
		TriangleGfxInfo.DrawClr = DrawClr;
		TriangleGfxInfo.FillClr = FillClr;
		TriangleGfxInfo.isFilled = isFilled;
		//Create a polygon with the above parameters

		Triangle* T = new Triangle(P1, P2, P3, TriangleGfxInfo);
		Addshape(T);
		}
		else if (getString(0, 2, line) == "Ova")
		{
		Point P1, P2;
		string holder;
		color DrawClr, FillClr;
		int start, end, Sborder;
		bool isFilled;

		border = line.back() - 48;		//Circle border

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
		if (getString(start, end, line) != "(N)") {	//if fill
			FillClr = Fcolor(getString(start, end, line));	//Fill color	
			isFilled = true;
		}
		else
		{
			isFilled = false;			//is not filled
		}



		//Constructing Circle
		//Intialzing Gfx infp
		GfxInfo OvalGfxInfo;
		OvalGfxInfo.BorderWdth = border;
		OvalGfxInfo.DrawClr = DrawClr;
		OvalGfxInfo.FillClr = FillClr;
		OvalGfxInfo.isFilled = isFilled;
		//Create a polygon with the above parameters
		Oval* C = new Oval(P1, P2, OvalGfxInfo);
		Addshape(C);
		}
		else if (getString(0, 2, line) == "Irr")
		{
		}
		else if (getString(0, 2, line) == "Lin") {
		Point P1, P2;
		string holder;
		color DrawClr, FillClr;
		int start, end, Sborder;
		bool isFilled;


		Sborder = line.back() - 48;		//Border

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
		if (getString(start, end, line) != "(N)") {	//if fill
			FillClr = Fcolor(getString(start, end, line));	//Fill color	
			isFilled = true;
		}
		else
		{
			isFilled = false;			//is not filled
		}



		//Constructing LineGfxInfo
		//Creating the line
		GfxInfo LineGfxInfo;
		LineGfxInfo.BorderWdth = Sborder;
		LineGfxInfo.DrawClr = DrawClr;
		LineGfxInfo.FillClr = FillClr;
		LineGfxInfo.isFilled = isFilled;
		//Create a polygon with the above parameters
		Line* L = new Line(P1, P2, LineGfxInfo);
		Addshape(L);
}
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
			clipboard.push_back(selected);	//problem: coppied item will have the same id
		}
	}
}

shape* Graph::GetSelectedShape()const
{
	return selectedShape;
}

vector<shape*> Graph::GetShapeList()const
{
	return shapesList;
}


void Graph::Paste() {
	//UnselectShape();	//unselect previous shape to select by defualt the copied
	for (auto& c_shape : clipboard) {
		const color pevClr = c_shape->getPevDrawClr();
		shape* Pasted_shape = c_shape->Clone();
		Pasted_shape->UpdateId();
		Pasted_shape->Shift(10,10);
		Pasted_shape->Selected(pevClr);
		Addshape(Pasted_shape);
	}
	ClipBoard(); //updates the clipboard with new shapes

}


bool Graph::getClipBoard() const {
	if (clipboard.size() > 0)
		return true;
	else
		return false;
}

void Graph::delShape(shape* selecetedshape) {
	for (unsigned int i = 0; i < shapesList.size(); i++) {

		if (selecetedshape ==shapesList[i]) {
			shapesList.erase(shapesList.begin() + i);
			delete selectedShape;
			selectedShape = nullptr;
		}

	}
}

void Graph::cut()
{
	UnSelectAll();
	shape* Cutted = selectedShape->Clone();
	clipboard.clear();
	clipboard.push_back(Cutted);
	delShape(selectedShape);
}

void Graph::PopFromShapeList(shape* PopMe) {
	for (int i = 0; i < shapesList.size(); i++)
	{
		if (shapesList[i] == PopMe)
		{
			shapesList.erase(shapesList.begin() + i);
		}
	}
}