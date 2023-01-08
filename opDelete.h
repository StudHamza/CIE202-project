


#pragma once
#include "operations/operation.h"
# include <vector>
	class opDelete :public operation
	{

	public:
		opDelete(controller* pCont);
		virtual ~opDelete();

		virtual void Execute();
		virtual void Undo()override;
		virtual void Redo()override;

	};


