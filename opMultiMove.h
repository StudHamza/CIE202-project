#pragma once
#include "operations/operation.h"
# include <vector>
class opMultiMove :public operation
{

public:
	opMultiMove(controller* pCont);
	virtual ~opMultiMove();

	virtual void Execute();

};


