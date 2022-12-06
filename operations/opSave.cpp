#include "opSave.h"
#include "..\shapes\RegPoly.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"
#include<fstream>


opSave::opSave(controller* pCont) :operation(pCont)
{}
opSave::~opSave()
{}

void opSave::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph=pControl->getGraph();
	pUI->PrintMessage("Write File name here: "); //Get file name
	string fileName = pUI->GetSrting();
	ofstream file;
	file.open(fileName + ".txt");

	pGraph->Save(file, pUI->getCrntDrawColor(), pUI->getCrntFillColor(), pUI->getCrntPenWidth());
	pUI->PrintMessage("Saved in " + fileName + " file");
}