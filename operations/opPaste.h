#pragma once


#pragma once

#include "operation.h"

//Add Rectangle operation class
class opPaste : public operation
{
public:
	opPaste(controller* pCont);
	virtual ~opPaste();

	//Add rectangle to the controller
	virtual void Execute();

};

