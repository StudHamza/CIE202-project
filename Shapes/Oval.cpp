#include "Oval.h"
#include <cmath>

Oval::Oval(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Radius1 = P1;
	Radius2 = P2;
	radiusX = abs(P1.x - P2.x)/2;
	radiusY = abs(P1.y - P2.y)/2;
	if (P1.x > P2.x) {
		Center.x = (radiusX + P2.x);
	}
	else if(P1.x < P2.x)
	{
		Center.x = (radiusX + P1.x);
	}
	if (P1.y > P2.y) {
		Center.y = (radiusY + P2.y);
	}
	else if (P1.y < P2.y)
	{
		Center.y = (radiusY + P1.y);
	}
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
	int res = (pow((x - Center.x), 2) / pow(radiusX, 2)) + (pow((y - Center.y), 2) / pow(radiusY, 2));
	if (res <= 1)
	{
		return true;
	}

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


void Oval::Resize(double scaling_factor) {
	int dx1;
	int dx2;
	int dy1;
	int dy2;

	dx1 = Radius1.x - Center.x;
	dy1 = Radius1.y - Center.y;
	dx2 = Radius2.x - Center.x;
	dy2 = Radius2.y - Center.y;

	Radius1.x = Center.x + (dx1 * scaling_factor);
	Radius1.y = Center.y + (dy1 * scaling_factor);
	Radius2.x = Center.x + (dx2 * scaling_factor);
	Radius2.y = Center.y + (dy2 * scaling_factor);





 }


 void Oval:: ResizebyDrag(int x, int y) {
//
//int dx1;
//int dx2;
//int dy1;
//int dy2;
//
//int dx1a = abs(x - Center.x)/2;
//int dy1a = y - Center.y;
//
//radiusX = 200+abs(Radius1.x - Radius2.x) / 2;
//
//radiusY = abs(Radius1.y - Radius2.y) / 2;
//
//int Rx = radiusX / dx1a;
//
//dx1 = Radius1.x - Center.x;
//dy1 = Radius1.y - Center.y;
//dx2 = Radius2.x - Center.x;
//dy2 = Radius2.y - Center.y;
//
//
//radiusX = abs(P1.x - P2.x) / 2;
//
//
//
//Radius1.x = Center.x + (dx1 *Rx);
//Radius1.y = Center.y + (dy1 *Rx);
//Radius2.x = Center.x + (dx2 *Rx);
//Radius2.y = Center.y + (dy2 *Rx);
//




 
 
 }





 void Oval::Move(int x, int y) {
	 int dx;
	 int dy;




	 dx = abs(Center.x - x);
	 dy = abs(Center.y - y);


	 if (x > Center.x) {
		 Radius1.x += dx;
		 Radius2.x += dx;
	 }
	 else
	 {
		 Radius1.x -= dx;
		 Radius2.x -= dx;


	 }

	 if (y > Center.y) {
		 Radius1.y += dy;
		 Radius2.y += dy;
	 }
	 else
	 {
		 Radius1.y -= dy;
		 Radius2.y -= dy;


	 }


	 if (Radius1.x > Radius2.x) {                            //centres must be redefiend with new vals after moving , scrambling or draggimg
		 Center.x = (radiusX + Radius2.x);
	 }
	 else if (Radius1.x < Radius2.x)
	 {
		 Center.x = (radiusX + Radius1.x);
	 }
	 if (Radius1.y > Radius2.y) {
		 Center.y = (radiusY + Radius2.y);
	 }
	 else if (Radius1.y < Radius2.y)
	 {
		 Center.y = (radiusY + Radius1.y);
	 }
 
 
 
 };
 void Oval::getXlimits(int& xMAX, int& xMIN) {             // used in multi move

	 xMAX = Center.x + radiusX;
	 xMIN = Center.x - radiusX;





 };   
 void Oval::getYlimits(int& yMAX, int& yMIN) {                      // used in multi move
 
 
	 yMAX = Center.y + radiusY;
	 yMIN = Center.y - radiusY;

 
 
 
 
 }; 





  void Oval::relative_move(int x1, int y1, int x2, int y2) {    //used in multi-move
	  Point centerS;        //center of a group of shapes

	  centerS.x = x1;
	  centerS.y = y1;
  
  
	  int dx;
	  int dy;




	  dx = abs(centerS.x - x2);
	  dy = abs(centerS.y - y2);


	  if (x2 > centerS.x) {
		  Radius1.x += dx;
		  Radius2.x += dx;
	  }
	  else
	  {
		  Radius1.x -= dx;
		  Radius2.x -= dx;


	  }

	  if (y2 > centerS.y) {
		  Radius1.y += dy;
		  Radius2.y += dy;
	  }
	  else
	  {
		  Radius1.y -= dy;
		  Radius2.y -= dy;


	  };


	  if (Radius1.x > Radius2.x) {
		  Center.x = (radiusX + Radius2.x);
	  }
	  else if (Radius1.x < Radius2.x)
	  {
		  Center.x = (radiusX + Radius1.x);
	  }
	  if (Radius1.y > Radius2.y) {
		  Center.y = (radiusY + Radius2.y);
	  }
	  else if (Radius1.y < Radius2.y)
	  {
		  Center.y = (radiusY + Radius1.y);
	  }
  
  
  
  
  
  }