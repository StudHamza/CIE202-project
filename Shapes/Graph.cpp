#include "Graph.h"
#include "../GUI/GUI.h"

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
		Box box = shapes->HitBox();
		if (x >= box.P1.x && x <= box.P2.x && y >= box.P1.y && y <= box.P2.y) { return shapes; } //Q is the shapes here a pointer?
	}

	///Add your code here to search for a shape given a point x,y	
	return nullptr;
}

string Graph::SelectShape(Point P, color pevClr,shape *selected)
{
	*pvp = P;
	return (selected->Selected(pevClr));
}
bool Graph::UnselectShape()
{
	if (!((*pvp).x==0 && (*pvp).y==0)) {
		shape* pSelected = Getshape((*pvp).x, (*pvp).y);
		if (pSelected) {
			if (pSelected->IsSelected()) {
				Getshape((*pvp).x, (*pvp).y)->UnSelect();
				*pvp = { 0,0 };
				return false;
			}
		}
	}
	else { return true; }
}



