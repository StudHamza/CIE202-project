#include "opClear.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"

opClear::opClear(controller* pCont) : operation(pCont) {}

opClear::~opClear() {
}



void opClear::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();
	pGraph->Clear();
}