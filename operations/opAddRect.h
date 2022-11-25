#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddRect: public operation
{
public:
	opAddRect(controller *pCont);
	virtual ~opAddRect();
	
	//Add rectangle to the controller
	virtual void Execute() ;
	
};

