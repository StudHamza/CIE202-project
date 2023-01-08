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
	centeroid.y = y;                       //setting the centroid to the new coordinates








}


void Triangle::Resize(double scaling_factor) {
	/*Point  midpoint1;*/ //midpoint for one of the sides




	int dx1;
	int dx2;
	int dy1;
	int dy2;
	int dx3;
	int dy3;


	dx1 = F.x - centeroid.x;
	dy1 = F.y - centeroid.y;
	dx2 = S.x - centeroid.x;
	dy2 = S.y - centeroid.y;
	dx3 = T.x - centeroid.x;
	dy3 = T.y - centeroid.y;

	F.x = centeroid.x + (dx1 * scaling_factor);
	F.y = centeroid.y + (dy1 * scaling_factor);
	S.x = centeroid.x + (dx2 * scaling_factor);
	S.y = centeroid.y + (dy2 * scaling_factor);
	T.x = centeroid.x + (dx3 * scaling_factor);
	T.y = centeroid.y + (dy3 * scaling_factor);




	//midpoint1.x = (F.x + S.x) / 2;
	//midpoint1.y = (F.y + S.y) / 2;

}



 void Triangle:: ResizebyDrag(int x, int y) {
	 Point midpoint1;

	 int dx1;
	 int dx2;
	 int dy1;
	 int dy2;
	 int dx3;
	 int dy3;

	 int dTx;
	 int dTy;

	 dx1 = F.x - centeroid.x;
	 dy1 = F.y - centeroid.y;
	 dx2 = S.x - centeroid.x;
	 dy2 = S.y - centeroid.y;
	 dx3 = T.x - centeroid.x;
	 dy3 = T.y - centeroid.y;

	 int dxa =x + centeroid.x;
	 int dya =y+ centeroid.y;
	 int dxb = x + centeroid.x;
	 int dyb = y + centeroid.y;
	 int dxc = x + centeroid.x;
	 int dyc = y + centeroid.y;

	 int R1 = abs(dx1 / dxa);
	 int R2 = abs(dy1 / dya);
	 int R3 = abs(dx2 / dxb);
	 int R4 = abs(dy2 / dxb);
	 int R5 = abs(dx3 / dxc);
	 int R6 = abs(dy3 / dxc);




		 



		


	 F.x = centeroid.x + (dx1*R1);
	 F.y = centeroid.y + (dy1 *R2);
	 S.x = centeroid.x + (dx2 *R3);
	 S.y = centeroid.y + (dy2 *R4);
	 T.x = centeroid.x + (dx3 *R5);
	 T.y = centeroid.y + (dy3 *R6);




	 midpoint1.x = (F.x + S.x) / 2;
	 midpoint1.y = (F.y + S.y) / 2;




}


//////////////////////multimove functions

 void Triangle:: relative_move(int x1, int y1, int x2, int y2) {


	 int dx, dy;


	 dx = abs(x1 - x2);
	 dy = abs(y1 - y2);
	 if (x2 >= x1) {
		 F.x += dx;
		 S.x += dx;
		 T.x += dx;
		 centeroid.x += dx;

	 }                                                    //changing vertices x coocrdinates

	 else {
		 F.x -= dx;
		 S.x -= dx;
		 T.x -= dx;
		 centeroid.x -= dx;
	

	 }





	 if (y2 >= y1) {
		 F.y += dy;
		 S.y += dy;
		 T.y += dy;
		 centeroid.y += dy;
	
	 }
	 //changing vertices y coordinates
	 else {
		 F.y -= dy;
		 S.y -= dy;
		 T.y -= dy;
		 centeroid.y -= dy;
	 }


	 centeroid.x += dx;
	 centeroid.y += dy;                       //setting the centroid to the new coordinates





};
void Triangle::getXlimits(int& xMAX, int& xMIN) {


	xMAX = max(F.x, S.x, T.x);
	xMIN = min(F.x, S.x, T.x);



};   // used in multi move
void Triangle:: getYlimits(int& yMAX, int& yMIN) {

	yMAX = max(F.y, S.y, T.y);

	yMIN = min(F.y, S.y, T.y);





}; // used in multi move
