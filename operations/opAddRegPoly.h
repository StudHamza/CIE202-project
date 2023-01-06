#pragma once

#include "operation.h"
class opAddRegPoly : public operation
{
	//Add Rectangle operation class

	public:
		opAddRegPoly(controller* pCont);
		virtual ~opAddRegPoly();

		//Add rectangle to the controller
		virtual void Execute();


		virtual void Undo()override;

};

