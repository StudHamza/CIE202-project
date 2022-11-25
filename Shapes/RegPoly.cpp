#include "RegPoly.h"


RegPoly::RegPoly(Point P1, Point P2,int S, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Center = P1;
	Start = P2;
	Side = S;
}

RegPoly::~RegPoly()
{}

void RegPoly::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRegPoly(Center, Start,Side, ShpGfxInfo);
}

