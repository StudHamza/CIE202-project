#pragma once

#include "operation.h"

class opCopy :public operation {
public:
	opCopy(controller* pCont);
	virtual ~opCopy();
	virtual void Execute();

};