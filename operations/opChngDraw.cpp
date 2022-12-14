#include "opChngDraw.h"


#include "..\controller.h"

#include "..\GUI\GUI.h"

opChngDraw::opChngDraw(controller* pCont) : operation(pCont) {}

opChngDraw::~opChngDraw() {}

void opChngDraw::Undo()
{
	GUI* pUI = pControl->GetUI();
	shape *shp=pControl->getOperatedOn();	//Get shape
	shp->ChngDrawClr(shp->UpdatePevDrawClr());	//Change color
}



void opChngDraw::Redo()
{
	cout << "not complete";
}

void opChngDraw::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGrph = pControl->getGraph();
	pUI->setCrntSelectedColor('d');
	if (pGrph->GetSelectedShape())
	{
		for (shape* fshape : pGrph->GetShapeList())
		{
			if (fshape->IsSelected()) {
				pControl->pushToOperatedOn(fshape);
				fshape->setPevDrawColors();
				fshape->UnSelect();
				fshape->ChngDrawClr(pUI->getCrntDrawColor());
			}
		}
	}
}