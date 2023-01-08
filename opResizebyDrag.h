#pragma once
#include "operations/operation.h"


class opResizebyDrag : public operation
{

public:
	opResizebyDrag(controller* pcont);


	virtual ~opResizebyDrag();

	virtual void Execute() override;



};