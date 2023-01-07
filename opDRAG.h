#pragma once
#include"operations/operation.h"



class opDRAG :public operation
{
public:
	opDRAG(controller* pcont);


	virtual ~opDRAG();

	virtual void Execute() override;


};

