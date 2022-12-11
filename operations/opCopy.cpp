#include "opCOPY.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"
#include <iostream>

opCopy::opCopy(controller* pCont) : operation(pCont) {}

opCopy::~opCopy() {
}



void opCopy::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGph = pControl->getGraph();
	if (pGph->GetSelectedShape())
	{
		pGph->ClipBoard();		//saves selected shapes into clipboard
		pUI->PrintMessage("iteam(s) copied to clipboard");
	}
	else
	{
		pUI->PrintMessage("There are not selected iteams");
	}
}