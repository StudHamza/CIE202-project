#pragma once
#include "operation.h"

class opChngDraw :public operation {
public:
	opChngDraw(controller* pCont);
	virtual ~opChngDraw();
	virtual void Execute();

};