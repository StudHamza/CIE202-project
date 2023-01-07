#pragma once
#include "operations/operation.h"

//Add Rectangle operation class
class opaddIREG : public operation
{
public:
	opaddIREG(controller* pcont);


	virtual ~opaddIREG();

	virtual void Execute();       //Add rectangle to the controller


};
