#include "Oval.h"
#include <cmath>

Oval::Oval(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Radius1 = P1;
	Radius2 = P2;
}

Oval::~Oval()
{}

void Oval::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawOval(Radius1, Radius2, ShpGfxInfo);
}



bool Oval::HitBox(int x, int y)const
{

		return false;
}


string Oval::GetInfo(char s)const
{
	string name, id, C, R, drawClr, fill, borderWidth, msg;
	color Draw = ShpGfxInfo.DrawClr;
	color Fill = ShpGfxInfo.FillClr;
	name = "Oval";
	id = to_string(ID);
	C = "(" + to_string(Radius1.x) + "," + to_string(Radius1.y) + ")";
	R = " (" + to_string(Radius2.x) + "," + to_string(Radius2.y) + ")";
	drawClr = Draw.getClr();

	fill = "(N)";
	if (ShpGfxInfo.isFilled) {
		fill = Fill.getClr();
	}

	borderWidth = to_string(ShpGfxInfo.BorderWdth);
	if (s == 's') {
		msg = name + " " + id + "  " + C + " radius " + R  + "Border width " + borderWidth;
		return msg;
	}
	msg = name + "," + id + "," + C + "," + R + "," + drawClr + "," + fill + "," + borderWidth;
	return msg;
}


void Oval::Shift(int dy, int dx) {

	Radius1.x += dx;
	Radius1.y += dy;
	Radius2.x += dx;
	Radius2.y += dy;

}


shape* Oval::Clone() {
	return new Oval(*this);
}

void Oval::Save(ofstream& file) const {
	string line = GetInfo('l');
	file << line << endl;
}