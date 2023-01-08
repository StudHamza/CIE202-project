#include "shape.h"
#include <iostream>

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

color shape::GetCrntColor() const
{
	return (ShpGfxInfo.DrawClr);
}
color shape::getPevDrawClr()const
{
	return ShpGfxInfo.PevDrawColors.back();
}
void shape::SetFill(bool isFilled)
{
	ShpGfxInfo.isFilled = isFilled;
}

void shape::Selected(color previousC)	//Sets shape to selected and gets info through a virtual function
{
	ShpGfxInfo.PrevClr=color(previousC);	//sets prev Color of selected shape
	SetSelected(true);	//sets selected to true
	ChngDrawClr(MAGENTA);		//change color
}

color shape::UpdatePevDrawClr() 
{
		color temp = ShpGfxInfo.PevDrawColors.back();
		ShpGfxInfo.PevFillColors.pop_back();
		return	temp;
}
color shape::UpdatePevFillClr()
{
	color pev = ShpGfxInfo.PevFillColors.back();
	ShpGfxInfo.PevFillColors.pop_back();
	return pev;
}
//Histoy//-----------------------------
void shape::setPevDrawColors()
{
	ShpGfxInfo.PevDrawColors.push_back(ShpGfxInfo.DrawClr);
	cout<<"Draw c size: "<< ShpGfxInfo.PevDrawColors.size() << endl;
}
void shape::setPevFillColors()
{
	ShpGfxInfo.PevFillColors.push_back(ShpGfxInfo.FillClr);
	cout << "Fil c size: " << ShpGfxInfo.PevFillColors.size() << endl;
}
//----------------------------------
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


void shape::UpdateId() {
	counter++;
	cout << "updated id: " << counter<<endl;
	ID = counter;
}

void shape::stickImage(image stick)
{
	sticked = stick;
}


int shape::counter = 0;

