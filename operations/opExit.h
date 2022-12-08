
#pragma once
#include "operation.h"

//Add Save operation pExit
class opExit : public operation
{
public:
	opExit(controller* pCont);
	virtual ~opExit();

	//Add rectangle to the controller
	virtual void Execute();

};