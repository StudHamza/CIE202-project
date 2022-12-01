#include "shape.h"

shape::shape(GfxInfo shapeGfxInfo)
{ 
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

string shape::Selected(color previousC)
{
	ShpGfxInfo.PrevClr=color(previousC);
	SetSelected(true);
	ChngDrawClr(MAGENTA);
	string msg = "Shape info:\tBorder Width "+to_string(ShpGfxInfo.BorderWdth)+"\tPen Color \t is selected\tfill color";
	return msg;
}

void shape::UnSelect()
{
	SetSelected(false);
	ChngDrawClr(ShpGfxInfo.PrevClr);
}