#include "opChngFill.h"


#include "..\controller.h"

#include "..\GUI\GUI.h"

opChngFill::opChngFill(controller* pCont) : operation(pCont) {}

opChngFill::~opChngFill() {}


void opChngFill::Undo()
{
	GUI* pUI = pControl->GetUI();
	shape* shp = pControl->getOperatedOn();	//Get shape
	shp->UpdatePevFillHistory();		//Updates the sequence of fill booleans
	if (shp->getFillHistory())
	{
		shp->ChngFillClr(shp->UpdatePevFillClr());	//Change color
	}
	else {
		shp->ChngFillClr(WHITE);
	}
	pControl->pushToFutureOperatedOn(shp);
}

void opChngFill::Redo()
{
	cout << "Not done i dont have time";
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
				shape->setPevFillColors();
				shape->SetFill(true);
				shape->ChngFillClr(pUI->getCrntFillColor());

			}
		}
	}
	else

	{
		pControl->DeleteTimeLine();
	}
}