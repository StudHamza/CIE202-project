#include "opSelect.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"

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

	pUI->PrintMessage("Select Shape");
	pUI->GetPointClicked(P.x, P.y);
	shape* SelectedShapeG = G->Getshape(P.x, P.y);
	if(SelectedShapeG){
		pUI->ClearStatusBar();
		color pevClr = pUI->getCrntDrawColor();
		string msg=G->SelectShape(P, pevClr,SelectedShapeG);
		pUI->PrintMessage(msg);
	}

}
