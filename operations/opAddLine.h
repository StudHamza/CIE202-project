
#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddLine : public operation
{
public:
	opAddLine(controller* pCont);
	virtual ~opAddLine();

	//Add rectangle to the controller
	virtual void Execute();


	virtual void Undo()override;

};