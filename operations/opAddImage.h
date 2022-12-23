#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddImage : public operation
{
public:
	opAddImage(controller* pCont);
	virtual ~opAddImage();

	//Add rectangle to the controller
	virtual void Execute();

};
