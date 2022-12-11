#include "opPaste.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opPaste::opPaste(controller* pCont) :operation(pCont)
{}
opPaste::~opPaste()
{}

//Execute the operation
void opPaste::Execute()
{	
	GUI* pUI = pControl->GetUI();	
	Graph* pGr = pControl->getGraph();
	if (pGr->getClipBoard()) {
	pGr->Paste();
	pUI->PrintMessage("Items have been pasted");
	}
	else
	{
		pUI->PrintMessage("Clip board is empty");
	}
}


