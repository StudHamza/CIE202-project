#include "opaddIREG.h"

#include "opaddIREG.h"
#include "IregularPoly.h"
#include "controller.h"
#include   "GUI/GUI.h"



opaddIREG::opaddIREG(controller* pcont) :operation(pcont)
{}

opaddIREG::~opaddIREG()
{}


void opaddIREG::Execute() {
	int sides;

	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New iregular polygon: enter no. of sides");



	sides = stoi(pUI->GetSrting());   // get number of sides

	int* arrayx = new int[sides];
	int* arrayy = new int[sides];

	string msg = "New iregular polygon: click at first corner";
	pUI->PrintMessage(msg);
	for (int i = 0; i < sides; i++)
	{

		pUI->GetPointClicked(arrayx[i], arrayy[i]);

		pUI->PrintMessage("clicked at(" + to_string(arrayx[i]) + ", " + to_string(arrayy[i]) + ")" + "click at corner number" + to_string(i + 2));



	}
	pUI->ClearStatusBar();

	//Preapre all iregpolygon parameters
	GfxInfo IREGpolGfxInfo;

	//get drawing, filling colors and pen width from the interface
	IREGpolGfxInfo.DrawClr = pUI->getCrntDrawColor(); ///////////////////////////////////////////////////////////////////////////////////////////
	IREGpolGfxInfo.FillClr = pUI->getCrntFillColor();
	IREGpolGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	IREGpolGfxInfo.isFilled = false;	//default is not filled
	IREGpolGfxInfo.isSelected = false;	//defualt is not selected


	//Create an iregpoly with the above parameters
	iregpoly* IR = new iregpoly(sides, arrayx,arrayy, IREGpolGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the rectangle to the list of shapes
	pGr->Addshape(IR);

}
