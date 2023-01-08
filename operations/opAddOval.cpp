#include "opAddoval.h"
#include "..\shapes\Oval.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddOval::opAddOval(controller* pCont) :operation(pCont)
{}
opAddOval::~opAddOval(){}

//Execute the operation
void opAddOval::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("Click on oval radius 1");
	//Read center of polygon and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "Start is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click on the ova radius 2";
	pUI->PrintMessage(msg);
	//Read start of polygon and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo OvalGfxInfo;

	//get drawing, filling colors and pen width from the interface
	color Fill, Draw;
	Fill = pUI->getCrntFillColor();
	Draw = pUI->getCrntDrawColor();
	OvalGfxInfo.DrawClr =Draw;
	OvalGfxInfo.FillClr = Fill;
	OvalGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	OvalGfxInfo.PrevClr = OvalGfxInfo.DrawClr;	//sets first color to draw color
	OvalGfxInfo.PevDrawColors.push_back(Draw);
	OvalGfxInfo.PevFillColors.push_back(Fill);


	OvalGfxInfo.isFilled = false;	//default is not filled
	OvalGfxInfo.FillHistory.push_back(false);
	OvalGfxInfo.isSelected = false;	//defualt is not selected
	OvalGfxInfo.isSaved = false;		//defualt is not save


	//Create a polygon with the above parameters
	Oval* O = new Oval(P1, P2, OvalGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the regular polygon to the list of shapes
	pGr->Addshape(O);

	//Update Operated on:
	pControl->pushToOperatedOn(O);
}


void opAddOval::Undo()
{
	shape* temp = pControl->getOperatedOn();
	Graph* Gpr = pControl->getGraph();
	Gpr->PopFromShapeList(temp);
}