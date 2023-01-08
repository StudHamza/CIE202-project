#include "opRESIZE.h"
#include "controller.h"
#include"GUI/GUI.h"



opRESIZE::opRESIZE(controller* pcont) :operation(pcont) {}


opRESIZE::~opRESIZE()
{}

void opRESIZE::Undo()
{
	float scaleFactor=1;
	shape* undoThis=pControl->getOperatedOn();	//get last shape
	scaleFactor = (1/(undoThis->getFactor()));	// Get last factor
	undoThis->Resize(scaleFactor);

	undoThis->popFactor();		//Remove last factor from history
}



void opRESIZE::Execute() {

	GUI* pUI = pControl->GetUI();
	Graph* ptG = pControl->getGraph();

	shape* selectedshsape = ptG->GetSelectedShape();

	if (selectedshsape) {

		pControl->pushToOperatedOn(selectedshsape);

		string factstr;

		double factor=1;

		pUI->PrintMessage("RESIZING 1 shape: choose a RESIZING factor---->2::4::0.5::0.25");

		factstr = pUI->GetSrting();

		if (factstr == "2")
			factor = 2;
		else if (factstr == "4")
			factor = 4;
		else if (factstr == "0.5")
			factor = 0.5;
		else if (factstr == "0.25")
			factor = 0.25;

		selectedshsape->setFactor(factor);
		selectedshsape->Resize(factor);
		selectedshsape->UnSelect();
		ptG->set_tonull();       //set selectedshape pointer to null ptr(unselect was not enoug)
		
	}
	else {
		pUI->PrintMessage("no shape is selecetd to be resized");
	}
}