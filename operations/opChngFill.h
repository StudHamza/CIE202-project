#pragma once

#include "operation.h"

class opChngFill :public operation {
public:
	opChngFill(controller* pCont);
	virtual ~opChngFill();
	virtual void Execute();
	virtual void Undo()override;
	virtual void Redo()override;

};