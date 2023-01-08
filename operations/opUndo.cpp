#include "opUndo.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <iostream>

opUndo::opUndo(controller* pCont) :operation(pCont)
{}
opUndo::~opUndo()
{}

//Execute the operation
void opUndo::Execute()
{
	//operationType op = pCont->UpdateTimeLine();
	operation* UnOp;
	if (pControl->checkPresent())
	{
		cout << "Excuting op: " << endl;
		UnOp=pControl->UpdateTimeLine();	//remove prev op and adds it to future
											//Also returns it
		UnOp->Undo();
		pControl->popOperatedOn();
	}

}
