#include "operation.h"
#pragma once

class opCut :public operation {
public:
	opCut(controller* pCont);
	virtual ~opCut();
	virtual void Execute();

}; 
