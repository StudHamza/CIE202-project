#pragma once
#include "operation.h"

class opUndo : public operation
{
public:
	opUndo(controller* pCont);
	virtual ~opUndo();

	virtual void Execute();
};
