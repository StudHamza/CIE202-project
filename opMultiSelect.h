#pragma once

#include"operations/operation.h"

class opSelect : public operation
{
public:
	opSelect(controller* pCont);
	virtual ~opSelect();
	//Add rectangle to the controller
	virtual void Execute();

};
