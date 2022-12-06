#include "Graph.h"
#include "../GUI/GUI.h"
#include <iostream>

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

}


