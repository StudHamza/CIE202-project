#pragma once
#include "operation.h"

//Add Save operation class
class opSave : public operation
{
public:
	opSave(controller* pCont);
	virtual ~opSave();

	//Add rectangle to the controller
	virtual void Execute();

};