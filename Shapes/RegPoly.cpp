#include "RegPoly.h"
#include <iostream>
#include <algorithm>
using namespace std;


RegPoly::RegPoly(Point P1, Point P2,int S, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Center = P1;
	Start = P2;
	Side = S;
	SetVertices();
}


void RegPoly::SetVertices() {
	float pi = 3.14159265358979323846;
	vector<int> VerX = { (Start.x-Center.x)};
	vector<int> VerY = { (Start.y-Center.y) };
	for (int i = 0; i < Side; i++)
	{
		int vx = ceil((VerX[i] * cos((2 * pi) / Side)) - (VerY[i] * sin((2 * pi) / Side))); //Matrix transofmation after translating to origin
		int vy = ceil((VerX[i] * sin((2 * pi) / Side)) + (VerY[i] * cos((2 * pi) / Side)));
		
		VerX.push_back(vx);
		VerY.push_back(vy);
	}
	for (int i = 0; i < Side; i++) { VerX[i]+= Center.x; VerY[i]+= Center.y; }
	Xv = VerX;
	Yv = VerY;
}


RegPoly::~RegPoly()
{}

void RegPoly::Draw(GUI* pUI) const
{
	
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRegPoly(Start,Xv,Yv ,Side, ShpGfxInfo);
}

bool RegPoly::HitBox(int x,int y)const //Not done yet
{

		int i, j, c = 0;
		for (i = 0, j = Side - 1; i < Side; j = i++) {
			if (((Yv[i] > y) != (Yv[j] > y)) &&
				(x < (Xv[j] - Xv[i]) * (y - Yv[i]) / (Yv[j] - Yv[i]) + Xv[i]))
				c = !c;
		}
		return c;
}


string RegPoly::GetInfo(char s)const	//current Draw,fill color and int border width
{
	string name,id,side,start, radius, drawClr, fill, borderWidth,msg;
	name = "Regular Polygon";
	id = to_string(ID);
	start = "(" + to_string(Center.x) + "," + to_string(Center.y) + ")";
	radius = " (" + to_string(Start.x) + "," + to_string(Start.y) + ")";
	drawClr = "("+to_string(ShpGfxInfo.DrawClr.ucRed) + ", " + to_string(ShpGfxInfo.DrawClr.ucBlue) + " ," + to_string(ShpGfxInfo.DrawClr.ucGreen)+")";
	fill = "(" + to_string(ShpGfxInfo.FillClr.ucRed) + " ," + to_string(ShpGfxInfo.FillClr.ucBlue) + ", " + to_string(ShpGfxInfo.FillClr.ucGreen)+")";
	borderWidth = to_string(ShpGfxInfo.BorderWdth);
	side = to_string(Side);
	if (s == 's') {
		msg = name+" " +id+" Center " +start+" Radius" +radius+" Draw Color" +drawClr+" Fill Color" +fill+" Border Width" +borderWidth;
		return msg;
	}
	msg = name + "," + id +","+ side+"," + start + "," + radius + "," + drawClr + "," + fill + "," + borderWidth;
	return msg;
}
