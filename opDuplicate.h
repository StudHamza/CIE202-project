#pragma once

#include "operations/operation.h"

class opDuplicate :public operation {
public:
	opDuplicate(controller* pCont);
	virtual ~opDuplicate();
	virtual void Execute();

};