#include "operation.h"

class opUndo : public operation
{
public:
	opUndo(controller* pCont);
	virtual ~opUndo();
	//Add rectangle to the controller
	virtual void Execute();
};
