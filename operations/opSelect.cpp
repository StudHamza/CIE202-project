#include "opSelect.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <iostream>

opSelect::opSelect(controller* pCont) :operation(pCont)
{}
opSelect::~opSelect()
{}

//Execute the operation
void opSelect::Execute()
{
	Point P;
	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();
	Graph* G = pControl->getGraph();

	G->UnselectShape();


	pUI->PrintMessage("Select Shape");
	pUI->GetPointClicked(P.x, P.y);
	shape* SelectedShapeG = G->Getshape(P.x, P.y);  //Gets clicked on shape if it is available
	if(SelectedShapeG){   //if selected
		pUI->ClearStatusBar(); 
		color pevClr = pUI->getCrntDrawColor(); //get crnt drawing pen color
		color pevFill = pUI->getCrntFillColor(); //Current fill color
		int  pevBorderW = pUI->getCrntPenWidth();	//pev width
		string msg=G->SelectShape(P, pevClr,SelectedShapeG);   //selecte shape and return msg (shape info)
		pUI->PrintMessage(msg);
	}
	else
	{
		pUI->PrintMessage("You selected nothing");
	}
}
