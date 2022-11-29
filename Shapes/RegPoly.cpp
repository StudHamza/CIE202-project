#include "RegPoly.h"
using namespace std;
#include <iostream>


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

