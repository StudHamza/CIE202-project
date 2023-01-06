#include "Circle.h"
#include <cmath>

Circle::Circle(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Center = P1;
	Start = P2;
	Radius = sqrt(pow((Center.x - Start.x), 2) + pow((Center.y - Start.y), 2));
}

Circle::~Circle()
{}

void Circle::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawCircle(Center, Radius, ShpGfxInfo);
}

void Circle::Move(int x, int y) {




	Center.x = x;
	Center.y = y;







}

bool Circle::HitBox(int x, int y)const
{
	double Hit;

	Hit = sqrt(pow((x - Center.x), 2) + pow((y - Center.y), 2));
	if (Hit <= Radius)
		return true;
	else
		return false;
}


string Circle::GetInfo(char s)const
{
	string name, id, C, R, drawClr, fill, borderWidth, msg;
	color Draw = ShpGfxInfo.DrawClr;
	color Fill = ShpGfxInfo.FillClr;
	name = "Circle";
	id = to_string(ID);
	C = "(" + to_string(Center.x) + "," + to_string(Center.y) + ")";
	R = " (" + to_string(Start.x) + "," + to_string(Start.y) + ")";
	drawClr = Draw.getClr();

	fill = "(N)";
	if (ShpGfxInfo.isFilled) {
		fill = Fill.getClr();
	}

	borderWidth = to_string(ShpGfxInfo.BorderWdth);
	if (s == 's') {
		msg = name + " " + id + "  " + C + " radius "+ R + " " + drawClr + " " + fill + " " + "Border width " + borderWidth;
		return msg;
	}
	msg = name + "," + id + "," + C + "," + R + "," + drawClr + "," + fill + "," + borderWidth;
	return msg;
}


void Circle::Shift(int dy, int dx) {

	Center.x += dx;
	Center.y += dy;
	Start.x += dx;
	Start.y += dy;

}


shape* Circle::Clone() {
	return new Circle(*this);
}

void Circle::Save(ofstream &file) const{
	string line = GetInfo('l');
	file << line << endl;
}


void Circle::relative_move(int x1, int y1, int x2, int y2) {

	int dx, dy;
	dx = abs(x1-x2);
	dy = abs(y1-y2);
	if(x2>x1)
	Center.x += dx;
	else
		Center.x -= dx;

	if(y2>y1)
     Center.y += dy;
	else
		Center.y -= dy;





}

void Circle::getXlimits(int& xMA,int& xMI) {

	int 	maxX = Center.x + Radius;
	int     minX =Center.x-Radius;


	xMA = maxX;
	
	xMI= minX;






} // used in multi move





void Circle::getYlimits(int& yMA, int& yMI) {

	int 	maxY = Center.y + Radius;
	int     minY = Center.y - Radius;


	yMA = maxY; 
	
	yMI=minY;






}


