#include "opAddRegPoly.h"
#include "..\shapes\RegPoly.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddRegPoly::opAddRegPoly(controller* pCont) :operation(pCont)
{}
opAddRegPoly::~opAddRegPoly()
{}

//Execute the operation
void opAddRegPoly::Execute()
{
	Point P1, P2;
	int side;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Regular Polygon: Click to the center of the polygon");
	//Read center of polygon and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "Center is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click on the starting point (radius)";
	pUI->PrintMessage(msg);
	//Read start of polygon and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();
	msg = "Please select the Number of side by typing into your keyboard then hitting ENTER: ";
	pUI->PrintMessage(msg);
	side=stoi(pUI->GetSrting());
	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo RegPolyGfxInfo;

	//get drawing, filling colors and pen width from the interface
	color Fill, Draw;
	Fill = pUI->getCrntFillColor();
	Draw = pUI->getCrntDrawColor();
	RegPolyGfxInfo.DrawClr = Draw;
	RegPolyGfxInfo.FillClr = Fill;
	RegPolyGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	RegPolyGfxInfo.PrevClr = RegPolyGfxInfo.DrawClr;	//sets first color to draw color
	RegPolyGfxInfo.PevDrawColors.push_back(Draw);
	RegPolyGfxInfo.PevFillColors.push_back(Fill);


	RegPolyGfxInfo.isFilled = false;	//default is not filled
	RegPolyGfxInfo.FillHistory.push_back(false);
	RegPolyGfxInfo.isSelected = false;	//defualt is not selected
	RegPolyGfxInfo.isSaved = false;		//defualt is not save


	//Create a polygon with the above parameters
	RegPoly* R = new RegPoly(P1, P2,side, RegPolyGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the regular polygon to the list of shapes
	pGr->Addshape(R);

	//Update Operated on:
	pControl->pushToOperatedOn(R);
}


void opAddRegPoly::Undo()
{
	shape* temp = pControl->getOperatedOn();
	Graph* Gpr = pControl->getGraph();
	Gpr->PopFromShapeList(temp);
	pControl->UpdateDelete(temp);
	pControl->popOperatedOn();
}