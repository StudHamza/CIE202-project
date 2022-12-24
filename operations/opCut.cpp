#include "opCut.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"
#include <iostream>

opCut::opCut(controller* pCont) : operation(pCont) {}

opCut::~opCut() {
}



void opCut::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGph = pControl->getGraph();
	if (pGph->GetSelectedShape())
	{
		pGph->cut();		//saves selected shapes into clipboard
		pUI->PrintMessage("iteam(s) copied to clipboard");
	}
	else
	{
		pUI->PrintMessage("There are not selected iteams");
	}

}