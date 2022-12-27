#include "opChngFill.h"


#include "..\controller.h"

#include "..\GUI\GUI.h"

opChngFill::opChngFill(controller* pCont) : operation(pCont) {}

opChngFill::~opChngFill() {}



void opChngFill::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGrph = pControl->getGraph();
	pUI->setCrntSelectedColor('f');
	pUI->PrintMessage("Fill color is setted");
	if (pGrph->GetSelectedShape())
	{
		for (shape* shape : pGrph->GetShapeList())
		{
			if (shape->IsSelected()) {
				shape->UnSelect();
				shape->SetFill(true);
				shape->ChngFillClr(pUI->getCrntFillColor());

			}
		}
	}


}