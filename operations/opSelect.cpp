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
	G->UnselectShape();
	G->UnSelectAll();


	pUI->PrintMessage("Select Shape (Hold shift to enable multi-select)");

	do {
		pUI->GetPointClicked(P.x, P.y);
		shape* SelectedShapeG = G->Getshape(P.x, P.y);  //Gets clicked on shape if it is available
		if (SelectedShapeG) {   //if selected
			pUI->ClearStatusBar();
			color pevClr =SelectedShapeG->GetCrntColor(); //get crnt drawing pen colo
			string msg = G->SelectShape(P, pevClr, SelectedShapeG);   //selecte shape and return msg (shape info)
			pUI->PrintMessage(msg);
			//G->set_selected_list();
			G->Draw(pUI);
		}
		else
		{
			pUI->PrintMessage("Shape not found");
		}
	} while (pUI->GetKeyClicked());
}
