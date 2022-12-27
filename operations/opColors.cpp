#include "opColors.h"


#include "..\controller.h"

#include "..\GUI\GUI.h"

opColors::opColors(controller* pCont) : operation(pCont) {}

opColors::~opColors() {}



void opColors::Execute()
{
	GUI* pUI = pControl->GetUI();
	string path= "images\\MenuIcons\\Colors.jpg";
	Point start={200,100}, end={900,400},P;
	pUI->DrawImage(path, start, end);
	pUI->GetPointClicked(P.x,P.y);
	color chosen = (pUI->getColor(P));
	if (pUI->getCrntSelectedColor() == 'd') {
		pUI->ChangeDrawColor(chosen);
	}
	else if (pUI->getCrntSelectedColor() == 'f')
	{
		pUI->ChangeFillColor(chosen);
	}
}