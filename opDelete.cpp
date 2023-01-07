#include "opDelete.h"
#include "controller.h"
#include "GUI/GUI.h"



opDelete::opDelete(controller* pcont) :operation(pcont)
{}
opDelete::~opDelete()
{}

void opDelete::Execute() {


	GUI* pUI = pControl->GetUI();
	Graph* ptG = pControl->getGraph();


	shape* selectedshape = ptG->GetSelectedShape();   //checks whether there are any shapes currently selected


	if (selectedshape) {

		ptG->delShape();

		pUI->PrintMessage("selected Shape(s) was deleted succesfully");
	}
	else {

		pUI->PrintMessage("No shape(s)  selected to be deleted");
	}





}