#pragma once
#include "operations/operation.h"
class opRESIZE : public operation
{

public:
	opRESIZE(controller* pcont);


	virtual ~opRESIZE();

	virtual void Execute() override;
	virtual void Undo()override;

};

