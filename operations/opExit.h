
#pragma once
#include "operation.h"

//Add Save operation pExit
class opExit : public operation
{
public:
	opExit(controller* pCont);
	virtual ~opExit();


	virtual void Execute();

};