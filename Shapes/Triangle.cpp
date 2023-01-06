#include "Triangle.h"
#include <cmath>


Triangle::Triangle(Point P1, Point P2,Point P3 ,GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	F = P1;
	S = P2;
	T = P3;
	 //to be used in move
	centeroid.x = (F.x + S.x + T.x) / 3;
	centeroid.y = (F.y + S.y + T.y) / 3;
}


Triangle::~Triangle()
{}

void Triangle::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawTriangle(F,S,T, ShpGfxInfo);
}



bool Triangle::HitBox(int x, int y)const		//from internet
{
	int as_x = x - F.x;
	int as_y = y - F.y;

	bool s_ab = (S.x - F.x) * as_y - (S.y - F.y) * as_x > 0;

	if ((T.x - F.x) * as_y - (T.y - F.y) * as_x > 0 == s_ab) return false;

	if ((T.x - S.x) * (y - S.y) - (T.y - S.y) * (x - S.x) > 0 != s_ab) return false;

	return true;
}


string Triangle::GetInfo(char s='s')const
{
	string name, id, P1, P2, P3 ,drawClr, fill, borderWidth, msg;
	color Draw = ShpGfxInfo.DrawClr;
	color Fill = ShpGfxInfo.FillClr;
	name = "Triangle";
	id = to_string(ID);
	P1 = "(" + to_string(F.x) + "," + to_string(F.y) + ")";
	P2 = " (" + to_string(S.x) + "," + to_string(S.y) + ")";
	P3 = " (" + to_string(T.x) + "," + to_string(T.y) + ")";
	drawClr = Draw.getClr();

	fill = "(N)";
	if (ShpGfxInfo.isFilled) {
		fill = Fill.getClr();
	}

	borderWidth = to_string(ShpGfxInfo.BorderWdth);
	if (s == 's') {
		msg = name + " " + id + " Point " + P1 + " Point2 " + P2 + " Point 3 "+ P3;
		return msg;
	}
	msg = name + "," + id + "," + P1 + "," + P2 + "," +P3+ "," + drawClr + "," + fill + "," + borderWidth;
	return msg;
}


void Triangle::Shift(int dy, int dx) {

	F.x += dx;
	F.y += dy;
	S.x += dx;
	S.y += dy;
	T.x += dx;
	T.y += dy;
}


shape* Triangle::Clone() {
	return new Triangle(*this);
}

void Triangle::Save(ofstream& file) const {
	string line = GetInfo('l');
	file << line << endl;
}


void Triangle::Move(int x, int y) {

	int dx, dy;


	dx = abs(centeroid.x - x);
	dy = abs(centeroid.y - y);
	if (x >= centeroid.x) {
		F.x += dx;
		S.x += dx;
		T.x += dx;
	}                                                    //changing vertices x coocrdinates

	else {
		F.x -= dx;
		S.x -= dx;
		T.x -= dx;

	}





	if (y >= centeroid.y) {
		F.y += dy;
		S.y += dy;
		T.y += dy;
	}
	//changing vertices y coordinates
	else {
		F.y -= dy;
		S.y -= dy;
		T.y -= dy;

	}


	centeroid.x = x;
	centeroid.y = y;                       //setting the centroid to the new one








}