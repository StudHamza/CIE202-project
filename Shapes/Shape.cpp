#include "shape.h"

shape::shape(GfxInfo shapeGfxInfo)
{	
	counter++;
	ID = counter;
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}
 
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

bool shape::IsSelected() const
{
	return ShpGfxInfo.isSelected;
}

void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}

void shape::Selected(color previousC)	//Sets shape to selected and gets info through a virtual function
{
	ShpGfxInfo.PrevClr=color(previousC);	//sets prev Color of selected shape
	SetSelected(true);	//sets selected to true
	ChngDrawClr(MAGENTA);		//change color
}

void shape::UnSelect()
{
	SetSelected(false);
	ChngDrawClr(ShpGfxInfo.PrevClr);
}


bool shape::IsSaved()
{
	return ShpGfxInfo.isSaved;
}


void shape::SetSaved(bool s)
{
	ShpGfxInfo.isSaved = s;
}






int shape::counter = 0;

