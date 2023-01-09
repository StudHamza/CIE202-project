//#include "opMatch.h"
//#include "controller.h"
//
//#include "GUI/GUI.h"
//#include <iostream>
//
//opMatch::opMatch(controller* pCont) : operation(pCont) {}
//
//opMatch::~opMatch() {
//}



//void opMatch::Execute()
//{
//	int x, y;
//	GUI* pUI = pControl->GetUI();
//	Graph* pGph = pControl->getGraph();
//	pUI->GetPointClicked(x,y);
//	shape* p1 = pGph->Getshape(x, y);
//	//p1->unhide();
//	//update graph();
//	pUI->GetPointClicked(x,y);
//	shape* p2 = pGph->Getshape(x, y);
//	//p2->unhide();
//	//update graph();
//	if (p1->getId() == p2->getId()) {
//		pGph->delShape(p1);
//		pGph->delShape(p2);
//		//increase score 3 
//	}
//	else {
//		Sleep(1000);
//		//p1->hide();
//		//p2->hide();
//		//decrease score 1 
//	}
//
//
//	
//	
//}