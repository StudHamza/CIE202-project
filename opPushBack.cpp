#include "opPushBack.h"
#include "controller.h"

#include "GUI/GUI.h"
#include <iostream>

opPushBack::opPushBack(controller* pCont) : operation(pCont) {}

opPushBack::~opPushBack() {
}



void opPushBack::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGph = pControl->getGraph();
	pGph->pushShapeBack();
}