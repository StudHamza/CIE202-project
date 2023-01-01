#include "opChngDraw.h"


#include "..\controller.h"

#include "..\GUI\GUI.h"

opChngDraw::opChngDraw(controller* pCont) : operation(pCont) {}

opChngDraw::~opChngDraw() {}

void opChngDraw::Undo()
{
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("undid");
	shape *shp=pControl->getOperatedOn();	//Get shape
	shp->ChngDrawClr(shp->getPevDrawClr());	//Change color

	pControl->popOperatedOn();

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
				fshape->setPevDrawClr();
				pControl->pushToOperatedOn(fshape);
				fshape->UnSelect();
				fshape->ChngDrawClr(pUI->getCrntDrawColor());
			}
		}
	}
}