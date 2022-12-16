#pragma once

#include "opAddLine.h"
#include "..\shapes\Line.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddLine::opAddLine(controller* pCont) :operation(pCont)
{}
opAddLine::~opAddLine()
{}

//Execute the operation
void opAddLine::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Line: Click at first Point");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First Point is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second Point";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo LineGfxInfo;

	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pUI->getCrntDrawColor();
	LineGfxInfo.FillClr = pUI->getCrntFillColor();
	LineGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	LineGfxInfo.PrevClr = LineGfxInfo.DrawClr;


	LineGfxInfo.isFilled = false;	//default is not filled
	LineGfxInfo.isSelected = false;	//defualt is not selected
	LineGfxInfo.isSaved = false;	//defualt is not saved


	//Create a rectangle with the above parameters
	Line* L = new Line(P1, P2, LineGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the rectangle to the list of shapes
	pGr->Addshape(L);

}
