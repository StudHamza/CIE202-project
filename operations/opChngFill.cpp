#include "opChngFill.h"


#include "..\controller.h"

#include "..\GUI\GUI.h"

opChngFill::opChngFill(controller* pCont) : operation(pCont) {}

opChngFill::~opChngFill() {}

void opChngFill::Undo()
{
	GUI* pUI = pControl->GetUI();
	shape* shp = pControl->getOperatedOn();	//Get shape
	shp->ChngFillClr(shp->getPevFillClr());	//Change color

	pControl->popOperatedOn();

}



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
				pControl->pushToOperatedOn(shape);	//always push modified shapes
				shape->UnSelect();
				cout << "I am unselecting the shape and setting pev color" << endl;
				shape->setPevFillColor();
				shape->SetFill(true);
				shape->ChngFillClr(pUI->getCrntFillColor());

			}
		}
	}


}