#pragma once
#include "operation.h"

class opColors :public operation {
public:
	opColors(controller* pCont);
	virtual ~opColors();
	virtual void Execute();

};