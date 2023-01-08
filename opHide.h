#pragma once


#include "operations/operation.h";

class opHide :public operation {
public:
	opHide(controller* pCont);
	virtual ~opHide();
	virtual void Execute();

};
