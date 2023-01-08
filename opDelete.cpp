#include "opDelete.h"
#include "controller.h"
#include "GUI/GUI.h"



opDelete::opDelete(controller* pcont) :operation(pcont)
{}
opDelete::~opDelete()
{}
void opDelete::Undo()
{
	shape* temp = pControl->getOperatedOn();
	Graph* Gpr = pControl->getGraph();
	Gpr->Addshape(temp);
	pControl->pushToFutureOperatedOn(temp);
}

void opDelete::Redo()
{
	shape* temp = pControl->getFutureOperatedOn();
	Graph* Gpr = pControl->getGraph();
	shape* cloned = temp->Clone();	//Dynamically allocated
	pControl->pushToOperatedOn(cloned);	//Used to store the shape incase of undo operation
	Gpr->deleteSingleShape(temp);
	pControl->pushToFutureOperatedOn(temp);
}

void opDelete::Execute() {


	GUI* pUI = pControl->GetUI();
	Graph* ptG = pControl->getGraph();


	shape* selectedshape = ptG->GetSelectedShape();   //checks whether there are any shapes currently selected


	if (selectedshape) {
		shape* cloned = selectedshape->Clone();	//Dynamically allocated
		pControl->pushToOperatedOn(cloned);	//Used to store the shape incase of undo operation
		ptG->delShape();

		pUI->PrintMessage("selected Shape(s) was deleted succesfully");
	}
	else {

		pUI->PrintMessage("No shape(s)  selected to be deleted");
	}





}