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

Box RegPoly::HitBox()const //Not done yet
{
	int max_x = *max_element(Xv.begin(), Xv.end());
	int max_y = *max_element(Yv.begin(), Yv.end());
	int min_x = *min_element(Xv.begin(), Xv.end());
	int min_y = *min_element(Yv.begin(), Yv.end());
	Point closest = { min_x, min_y };
	Point farthest = { max_x, max_y };
	Box HBox = { closest,farthest };
	return HBox;
}
