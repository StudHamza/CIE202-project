#include "operation.h"

class opClear :public operation {
public:
	opClear(controller* pCont);
	virtual ~opClear();
	virtual void Execute();

};