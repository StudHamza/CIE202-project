#pragma once
#include "operations/operation.h"
# include <vector>
class opScramble :public operation
{

public:
	opScramble(controller* pCont);
	virtual ~opScramble();

	virtual void Execute();

};
