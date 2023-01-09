#include "shape.h"
#include <iostream>

shape::shape(GfxInfo shapeGfxInfo)
{	
	counter++;
	ID = counter;
	shapeGfxInfo.FillHistory.push_back(false);
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}
 
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

bool shape::IsSelected() const
{
	return ShpGfxInfo.isSelected;
}
int shape::getId() {
	return ID;
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
bool shape::getFillHistory()const
{
	return ShpGfxInfo.FillHistory.back();
}
void shape::SetFill(bool isFilled)
{
	ShpGfxInfo.FillHistory.push_back(isFilled);
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
		ShpGfxInfo.FutureDrawClr.push_back(temp);
		ShpGfxInfo.PevFillColors.pop_back();
		return	temp;
}
color shape::UpdatePevFillClr()
{
	if (ShpGfxInfo.FillHistory.back())
	{
		color pev = ShpGfxInfo.PevFillColors.back();
		ShpGfxInfo.FutureFillClr.push_back(pev);
		ShpGfxInfo.PevFillColors.pop_back();
		return pev;
	}
	return FRAME;
}
//Histoy//-----------------------------
void shape::setPevDrawColors()
{
	ShpGfxInfo.PevDrawColors.push_back(ShpGfxInfo.PrevClr);
}
void shape::setPevFillColors()
{
	ShpGfxInfo.PevFillColors.push_back(ShpGfxInfo.FillClr);
}
void shape::UpdatePevFillHistory()
{
	ShpGfxInfo.FutureFillHistory.push_back(ShpGfxInfo.FillHistory.back());
	ShpGfxInfo.FillHistory.pop_back();
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
	ID = counter;
}

void shape::stickImage(image stick)
{
	sticked = stick;
}


int shape::counter = 0;


//////////////////////////////////Redo and undo
float shape::getFactor()const		//Gets last resized with factor
{
	return ShpGfxInfo.ResizeFactors.back();
}
void shape::setFactor(float factor) {		//Sets factor of resize
	ShpGfxInfo.ResizeFactors.push_back(factor);
}
void shape::popFactor()		//Removes last resize factor from history
{
	ShpGfxInfo.FutureResize.push_back(ShpGfxInfo.ResizeFactors.back());
	ShpGfxInfo.ResizeFactors.pop_back();
}

void shape::setPevPoint(Point p) {
	ShpGfxInfo.PevMovedFrom.push_back(p);
}
Point shape::OnlyGetPevPoint()
{
	return ShpGfxInfo.PevMovedFrom.back();
}

Point shape::GetPevPoint()
{
	Point Temp;
	Temp = ShpGfxInfo.PevMovedFrom.back();
	ShpGfxInfo.PevMovedFrom.pop_back();
	return Temp;
}

void shape::setFuturePoint(Point P)
{
	ShpGfxInfo.FutureMovedFrom.push_back(P);
}

Point shape::updateFuturePoint()
{
	Point temp;
	temp = ShpGfxInfo.FutureMovedFrom.back();
	ShpGfxInfo.FutureMovedFrom.pop_back();
	return temp;
}

void shape::setFutureDrawColor(color c)
{
	ShpGfxInfo.FutureDrawClr.push_back(c);
}
void shape::setFutureFillColor(color c)
{
	ShpGfxInfo.FutureFillClr.push_back(c);
}
color shape::updateFutureDraw()
{
	color Temp;
	Temp = ShpGfxInfo.FutureDrawClr.back();;
	ShpGfxInfo.FutureDrawClr.pop_back();
	return Temp;
}
color shape::updateFutureFill()
{
	color Temp;
	Temp = ShpGfxInfo.FutureFillClr.back();;
	ShpGfxInfo.FutureFillClr.pop_back();
	return Temp;
}