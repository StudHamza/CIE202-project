
#pragma once
#include "operation.h"

//Add Save operation class
class opLoad : public operation
{
public:
	opLoad(controller* pCont);
	virtual ~opLoad();

	//Add rectangle to the controller
	virtual void Execute();

};