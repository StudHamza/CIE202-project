#include "opAddCircle.h"
#include "..\shapes\Circle.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddCircle::opAddCircle(controller* pCont) :operation(pCont)
{}
opAddCircle::~opAddCircle()
{}

//Execute the operation
void opAddCircle::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("Click on circle centre");
	//Read center of polygon and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "Center is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click on the starting point (radius)";
	pUI->PrintMessage(msg);
	//Read start of polygon and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo CircleGfxInfo;

	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pUI->getCrntDrawColor();
	CircleGfxInfo.FillClr = pUI->getCrntFillColor();
	CircleGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	CircleGfxInfo.PrevClr = CircleGfxInfo.DrawClr;	//sets first color to draw color


	CircleGfxInfo.isFilled = false;	//default is not filled
	CircleGfxInfo.isSelected = false;	//defualt is not selected
	CircleGfxInfo.isSaved = false;		//defualt is not save


	//Create a polygon with the above parameters
	Circle* C = new Circle(P1, P2, CircleGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the regular polygon to the list of shapes
	pGr->Addshape(C);

	//Update Operated on:
	pControl->pushToOperatedOn(C);

}



void opAddCircle::Undo()
{
	shape* temp = pControl->getOperatedOn();
	Graph* Gpr = pControl->getGraph();
	Gpr->PopFromShapeList(temp);
	pControl->UpdateDelete(temp);
	pControl->popOperatedOn();
}


