#include "opLoad.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <fstream>

opLoad::opLoad(controller* pCont) :operation(pCont)
{}
opLoad::~opLoad()
{}

void opLoad::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* pGP = pControl->getGraph();
	pUI->PrintMessage("Type the file name: ");
	string fileName=pUI->GetSrting()+".txt";
	ifstream file(fileName);
	if (file) {
		pGP->load(file);
	}
	else {
		pUI->PrintMessage("There is no such file");
	}
	pUI->ClearStatusBar();

}