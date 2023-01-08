#include "IregularPoly.h"



iregpoly::iregpoly(int sidesnum, int* arrayx,int* arrayy, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	 numsides = sidesnum;
	 array_ofxs = arrayx;
	 array_ofys = arrayy;

};

iregpoly:: ~iregpoly() {

	delete array_ofxs;
	array_ofxs = nullptr;
	
	delete array_ofys;
	array_ofys = nullptr;

};


//call output>>draw an ireggular polygon on the screen

void iregpoly::Draw(GUI* pUI) const {
	pUI->DrawIREG( numsides,  array_ofxs,  array_ofys, ShpGfxInfo);

};

/////////////////////////////////UNDONE///////////////////////////////////////////////////

bool iregpoly::HitBox(int x, int y)const
{
	return false;
}


string iregpoly::GetInfo(char s)const
{
	return "no";
}


void iregpoly::Shift(int dy, int dx) {
	for (int i = 0; i < numsides; i++)
	{
		array_ofxs[i]+dx;
		array_ofys[i]+dy;
	}
}


shape* iregpoly::Clone() {
	return new iregpoly(*this);
}

void iregpoly::Save(ofstream& file) const {
	//string line = GetInfo('l');
	//file << line << endl;
}