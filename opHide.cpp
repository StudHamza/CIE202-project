#include "opHide.h"






#include "controller.h"
#include "GUI/GUI.h"




opHide::opHide(controller* pcont) :operation(pcont) {

}

opHide::~opHide()
{}


void opHide::Execute() {

	GUI* pUI = pControl->GetUI();



	Graph* ptG = pControl->getGraph();

	cout << "hide" << endl;
string x="images\\MenuIcons\\Menu_MULTIMOVE.jpg";

ptG->sethide();

	


	

	




}
