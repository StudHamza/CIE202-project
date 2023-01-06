#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddTriangle : public operation
{
public:
	opAddTriangle(controller* pCont);
	virtual ~opAddTriangle();

	//Add rectangle to the controller
	virtual void Execute();


	virtual void Undo()override;

};
