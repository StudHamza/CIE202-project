#include "RegPoly.h"
#include <iostream>
#include <algorithm>
using namespace std;



RegPoly::RegPoly(Point P1, Point P2,int S, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Center = P1;
	Start = P2;
	Side = S;
	Radius = sqrt(pow((Center.x - Start.x), 2) + pow((Center.y - Start.y), 2));
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

bool RegPoly::HitBox(int x,int y)const //From internet
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
	color fc, dc;
	name = "Regular Polygon";
	id = to_string(ID);
	start = "(" + to_string(Center.x) + "," + to_string(Center.y) + ")";
	radius = " (" + to_string(Start.x) + "," + to_string(Start.y) + ")";
	dc = ShpGfxInfo.DrawClr;
	drawClr = dc.getClr();
	fc = ShpGfxInfo.FillClr;
	fill = "(N)";
	if (ShpGfxInfo.isFilled) {
		fill = fc.getClr();
	}
	borderWidth = to_string(ShpGfxInfo.BorderWdth);
	side = to_string(Side);
	if (s == 's') {
		msg = name+" " +id+" Center " +start+" Radius" +radius+" Draw Color" +drawClr+" Fill Color" +fill+" Border Width" +borderWidth;
		return msg;
	}
	msg = name + "," + id +","+ side+"," + start + "," + radius + "," + drawClr + "," + fill + "," + borderWidth;
	return msg;
}


void RegPoly::Shift(int dy, int dx) {
	for (int i = 0; i < Side; i++) {
		Xv[i] += dx;
		Yv[i] += dy;
	}
	Start.x += dx;
	Start.y += dy;
	Center.x += dx;
	Center.y += dy;
}


shape* RegPoly::Clone() {
	return new RegPoly(*this);
}

void RegPoly::Save(ofstream &file)const {
	string line = GetInfo('l');	//get load info
	file << line << endl;
}



void RegPoly::Resize(double scaling_factor) {

	int dx;
	int dy;

	for (unsigned int i = 0; i < Xv.size(); i++) {

		dx = Xv[i] - Center.x;
		dy = Yv[i] - Center.y;
		Xv[i] = Center.x + (dx * scaling_factor);
		Yv[i] = Center.y + (dy * scaling_factor);




	}
}

 void RegPoly:: ResizebyDrag(int x, int y) {
	 
		 Start.x = x;
	     Start.y = y;


		 Radius = sqrt(pow((Center.x - Start.x), 2) + pow((Center.y - Start.y), 2));


		 float pi = 3.14159265358979323846;
		 vector<int> VerX = { (Start.x - Center.x) };
		 vector<int> VerY = { (Start.y - Center.y) };
		 for (int i = 0; i < Side; i++)
		 {
			 int vx = ceil((VerX[i] * cos((2 * pi) / Side)) - (VerY[i] * sin((2 * pi) / Side))); //Matrix transofmation after translating to origin
			 int vy = ceil((VerX[i] * sin((2 * pi) / Side)) + (VerY[i] * cos((2 * pi) / Side)));

			 VerX.push_back(vx);
			 VerY.push_back(vy);
		 }
		 for (int i = 0; i < Side; i++) { VerX[i] += Center.x; VerY[i] += Center.y; }
		 Xv = VerX;
		 Yv = VerY;



}







///////////////////MULTIMOVE FUNCTIONS



void RegPoly:: getXlimits(int& xMAX, int& xMIN) {
	int T1 = 0, T2 = 3000;
	int x1, x2;
	
	/*for (int i = 0; i < Side; i++) {
		
		x1 = max(Xv[i],T1);
		x2 = min(Xv[i],T2);

		T1 = Xv[i];
		T2 = Xv[i];


	}

	xMAX = x1;
	xMIN = x2;*/
	xMAX = Start.x + Radius;
	xMIN = Start.x - Radius;

	



};   // used in multi move
void RegPoly::getYlimits(int& yMAX, int& yMIN) {
	//int T1 = 0, T2 = 3000;
	//int y1, y2;

	//for (int i = 0; i < Side; i++) {

	//	y1 = max(Yv[i], T1);
	//	y2 = min(Yv[i], T2);

	//	T1 = Xv[i];
	//	T2 = Xv[i];


	//}



	//yMAX = y1;
	//yMIN = y2;

	yMAX = Start.y + Radius;
	yMIN = Start.y - Radius;








}; // used in multi move
 void RegPoly:: relative_move(int x1, int y1, int x2, int y2) {

	 int dx;
	 int dy;
	 Point C;

	C.x = x1;
C.y = y1;

	 dx = abs(C.x - x2);
	 dy = abs(C.y - y2);
	 int dx2, dy2;


	 dx2 = abs(Start.x - x2);
	 dy2 = abs(Start.y - y2);

	 for (int i = 0; i < Side; i++) {
		 if (x2 > C.x)
			 Xv[i] += dx;
		 else
			 Xv[i] -= dx;
	 }


	 for (int i = 0; i < Side; i++) {
		 if (y2 > C.y)

			 Yv[i] += dy;
		 else
			 Yv[i] -= dy;


	 }

	 if (y2 > C.y) {

		 this->Center.y += dy;
		 
	 }
	 else
	 {
		 this->Center.y -= dy;
		


	 }
	 if (x2 >= C.x)
		 this->Center.x += dx;
	 else	 
		 this->Center.x -= dx;

	 if (y2 > Start.y)
		 Start.y += dy2;
	 else
		 Start.y -= dy2;

	 if (x2 > Start.x)
		 Start.x += dx2;
	 else
		 Start.x -=dx2;




	 Radius = sqrt(pow((Center.x - Start.x), 2) + pow((Center.y - Start.y), 2));





 }


	









