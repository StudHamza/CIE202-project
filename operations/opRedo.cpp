#include "opRedo.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <iostream>

opRedo::opRedo(controller* pCont) :operation(pCont)
{}
opRedo::~opRedo()
{}

//Execute the operation
void opRedo::Execute()
{
	//operationType op = pCont->UpdateTimeLine();
	operation* UnOp;
	if (pControl->checkFuture())
	{
		UnOp = pControl->UpdateFuture();	//remove prev op and adds it to future
		UnOp->Redo();
		pControl->popOperatedOnToPresent();
	}

}