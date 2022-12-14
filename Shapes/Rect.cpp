#include "Rect.h"


Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2; 


	centeroid.x = ((P1.x + P2.x) / 2);
	centeroid.y = ((P1.y + P2.y) / 2);

}

Rect::~Rect()
{}

void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}



bool Rect::HitBox(int x,int y)const
{
	Box HBox;
	if (Corner1.x < Corner2.x && Corner1.y < Corner2.y) {
		HBox = { Corner1,Corner2 };
	}
	else {
		HBox = { Corner2,Corner1 };
	}
	if (x >= HBox.P1.x && x <= HBox.P2.x && y >= HBox.P1.y && y <= HBox.P2.y) { return true; }
	return false;
}


string Rect::GetInfo(char s)const
{
	string name,id,c1, c2, drawClr, fill, borderWidth,msg;
	color Draw=ShpGfxInfo.DrawClr;
	color Fill = ShpGfxInfo.FillClr;
	name = "Rectangle";
	id = to_string(ID);
	c1 = "(" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ")";
	c2 = " (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")"; 
	drawClr = Draw.getClr();

	fill = "(N)";
	if (ShpGfxInfo.isFilled) {
		fill = Fill.getClr();
	}

	borderWidth = to_string(ShpGfxInfo.BorderWdth);
	if (s == 's') {
		msg = name+" " +id+" corner1 " +c1+" corner2 " +c2+" " +drawClr+" " +fill+" " +"Border width "+borderWidth;
		return msg;
	}
	msg = name+","+id+","+c1+","+c2+","+drawClr+","+fill+","+borderWidth;
	return msg;
}


void Rect::Shift(int dy, int dx) {
	Corner1.x += dx;
	Corner1.y += dy;
	Corner2.x += dy;
	Corner2.y += dy;
}


shape* Rect::Clone() {
	return new Rect(*this);
}

void Rect::Save(ofstream& file) const{
	string line = GetInfo('l');
	file << line << endl;
}



void Rect::Move(int x, int y) {
	int dx, dy;


	dx = abs(centeroid.x - x);
	dy = abs(centeroid.y - y);
	if (x >= centeroid.x) {
		Corner1.x += dx;
		Corner2.x += dx;

	}                                                    //changing vertices x coocrdinates

	else {
		Corner1.x -= dx;
		Corner2.x -= dx;


	}





	if (y >= centeroid.y) {
		Corner1.y += dy;
		Corner2.y += dy;

	}
	//changing vertices y coordinates
	else {
		Corner1.y -= dy;
		Corner2.y -= dy;


	}


	centeroid.x = x;
	centeroid.y = y;                       //setting the centroid to the new one








}




void Rect::Resize(double scaling_factor) {

	int dx1;
	int dx2;
	int dy1;
	int dy2;


	dx1 = Corner1.x - centeroid.x;
	dy1 = Corner1.y - centeroid.y;
	dx2 = Corner2.x - centeroid.x;
	dy2 = Corner2.y - centeroid.y;

	Corner1.x = centeroid.x + (dx1 * scaling_factor);
	Corner1.y = centeroid.y + (dy1 * scaling_factor);
	Corner2.x = centeroid.x + (dx2 * scaling_factor);
	Corner2.y = centeroid.y + (dy2 * scaling_factor);

}



 void Rect:: ResizebyDrag(int x, int y) {
	 int dx1;
	
	 int dy1;

	 Corner1.x = x;
	 Corner1.y = y;


	int  d = sqrt(pow((Corner1.x - centeroid.x), 2) + pow((Corner1.y - centeroid.y), 2));
	 dx1 = Corner1.x - centeroid.x;
	 dy1 = Corner1.y - centeroid.y;
	
	int Radius1 = sqrt(pow((centeroid.x - x), 2) + pow((centeroid.y - y), 2));
 
	int R1 = Radius1 / d;



	 Corner1.x = centeroid.x + (dx1*R1);
	 Corner1.y = centeroid.y + (dy1*R1);
	 Corner2.x = centeroid.x - (dx1*R1);
	 Corner2.y = centeroid.y - (dy1*R1);




}


//multimove functions
 void Rect::relative_move(int x1, int y1, int x2, int y2) {              
 
	 //Point centerS;         //center for a gp of shapes
 
	 //centerS.x = centeroid.x;
	 //centerS.y = centeroid.y;
 
	 int dx, dy;


	 dx = abs(x1- x2);
	 dy = abs(y1 - y2);
	 if (x2 >= x1) {
		 Corner1.x += dx;
		 Corner2.x += dx;

	 }                                                    //changing vertices x coocrdinates

	 else {
		 Corner1.x -= dx;
		 Corner2.x -= dx;


	 }





	 if (y2 >= y1) {
		 Corner1.y += dy;
		 Corner2.y += dy;

	 }
	 //changing vertices y coordinates
	 else {
		 Corner1.y -= dy;
		 Corner2.y -= dy;


	 }

	 centeroid.x = ((Corner1.x + Corner2.x) / 2);
	 centeroid.y = ((Corner1.y + Corner2.y) / 2);                     //setting the centroid to its new vals(not the new destination )

 
 
 };





 void Rect::getXlimits(int& xMAX, int& xMIN) {
	

	 xMAX = max(Corner1.x, Corner2.x);
	 xMIN = min(Corner1.x, Corner2.x);



 };   // used in multi move
 void Rect::getYlimits(int& yMAX, int& yMIN) {


	 yMAX = max(Corner1.y, Corner2.y);
	 yMIN = min(Corner1.y, Corner2.y);




 }; // used in multi move