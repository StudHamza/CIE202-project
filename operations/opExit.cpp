#include "opExit.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"

opExit::opExit(controller* pCont) :operation(pCont)
{}
opExit::~opExit()
{}

void opExit::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* pGP = pControl->getGraph();
	if (pGP->Exit()) {
		pUI->SetExit(pUI->CreateWind(600, 300, 200, 200));
		pUI->PrintExitMessage("There are still unsaved files, do you wish to continue?(Y/n)");
		string answer;
		do {
			answer = pUI->GetSrting('d');
			if (answer == "Y") {
				exit(1);
			}
			else if (answer == "n")
			{
				pUI->DeleteExitWind();
				break;
			}
			else {
				pUI->PrintExitMessage("Not valid answer,choose from (Y/n)", 'd');
			}
		} while (answer != "n" || answer != "Y");
	}
	else
		exit(0);
}

