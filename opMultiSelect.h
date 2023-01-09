#pragma once

#include"operations/operation.h"

class opMultiSelect : public operation
{
public:
	opMultiSelect(controller* pCont);
	virtual ~opMultiSelect();
	virtual void Execute();

};
