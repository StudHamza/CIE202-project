#include "Rect.h"


Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2; 
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