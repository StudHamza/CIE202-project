#pragma once

#include "operations/operation.h"

class opPushBack :public operation {
public:
	opPushBack(controller* pCont);
	virtual ~opPushBack();
	virtual void Execute();

};