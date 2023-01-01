#include "Line.h"
#include <cmath>


Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Start = P1;
	End = P2;
	Distance = sqrt(pow(Start.x - End.x, 2) + pow(Start.y - End.y, 2));
	midpoint.x = (Start.x + End.x) / 2;
	midpoint.y = (Start.y + End.y) / 2;
}

Line::~Line()
{}

void Line::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawLine(Start, End, ShpGfxInfo);
}



bool Line::HitBox(int x, int y)const
{

	double AP = sqrt(pow(Start.x - x, 2) + pow(Start.y - y, 2));
	double BP = sqrt(pow(End.x - x, 2) + pow(End.y - y, 2));
	if ((AP+BP)-Distance<0.1&& (AP + BP) - Distance > -0.1)
		return true;
    return false;
}


string Line::GetInfo(char s)const
{
	string name, id, c1, c2, drawClr, fill, borderWidth, msg;
	color Draw = ShpGfxInfo.DrawClr;
	color Fill = ShpGfxInfo.FillClr;
	name = "Line";
	id = to_string(ID);
	c1 = "(" + to_string(Start.x) + "," + to_string(Start.y) + ")";
	c2 = " (" + to_string(End.x) + "," + to_string(End.y) + ")";
	drawClr = Draw.getClr();

	fill = "(N)";
	if (ShpGfxInfo.isFilled) {
		fill = Fill.getClr();
	}

	borderWidth = to_string(ShpGfxInfo.BorderWdth);
	if (s == 's') {
		msg = name + " " + id + " Start " + c1 + " End " + c2 + " ";
		return msg;
	}
	msg = name + "," + id + "," + c1 + "," + c2 + "," + drawClr + "," + fill + "," + borderWidth;
	return msg;
}


void Line::Shift(int dy, int dx) {
	Start.x += dx;
	Start.y += dy;
	End.x += dy;
	End.y += dy;
}


shape* Line::Clone() {
	return new Line(*this);
}

void Line::Save(ofstream& file) const {
	string line = GetInfo('l');
	file << line << endl;
}

void Line::Move(int x, int y) {

	int dx;
	int dy;




	dx = abs(midpoint.x - x);
	dy = abs(midpoint.y - y);


	if (x > midpoint.x) {
		Start.x += dx;
		End.x += dx;
	}
	else
	{
		Start.x -= dx;
		End.x -= dx;


	}

	if (y > midpoint.y) {
		Start.y += dy;
		End.y += dy;
	}
	else
	{
		Start.y -= dy;
		End.y -= dy;


	}

	midpoint.x = (Start.x + End.x) / 2;
	midpoint.y = (Start.y + End.y) / 2;

	cout << dx << endl;
	cout << dy << endl;

}