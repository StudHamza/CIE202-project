#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddCircle : public operation
{
public:
	opAddCircle(controller* pCont);
	virtual ~opAddCircle();

	//Add rectangle to the controller
	virtual void Execute();


	virtual void Undo()override;

	virtual void Redo()override;

};
