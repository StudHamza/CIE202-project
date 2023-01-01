#include "opScramble.h"
#include "controller.h"
#include "GUI/GUI.h"




opScramble::opScramble(controller* pcont) :operation(pcont) {

}

opScramble::~opScramble()
{}


void opScramble::Execute() {

	GUI* pUI = pControl->GetUI();
	Graph* ptG = pControl->getGraph();

	ptG->random_move();

	pUI->PrintMessage("Shapes has been scrambled ");




}
