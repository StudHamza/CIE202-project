#include "opChngDraw.h"


#include "..\controller.h"

#include "..\GUI\GUI.h"

opChngDraw::opChngDraw(controller* pCont) : operation(pCont) {}

opChngDraw::~opChngDraw() {}



void opChngDraw::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGrph = pControl->getGraph();
	pUI->setCrntSelectedColor('d');
	if (pGrph->GetSelectedShape())
	{
		for (shape* shape : pGrph->GetShapeList())
		{
			if (shape->IsSelected()) {
				shape->UnSelect();
				shape->setPevDrawClr();
				shape->ChngDrawClr(pUI->getCrntDrawColor());

			}
		}
	}
}