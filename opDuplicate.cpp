#include "opDuplicate.h"
#include "controller.h"

#include "GUI/GUI.h"
#include <iostream>

opDuplicate::opDuplicate(controller* pCont) : operation(pCont) {}

opDuplicate::~opDuplicate() {
}



void opDuplicate::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGph = pControl->getGraph();
	pGph->Duplicate();
}