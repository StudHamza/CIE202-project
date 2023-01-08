#pragma once

#include "Shapes/Shape.h"





class iregpoly : public shape
{
private:











	int numsides;
	int* array_ofxs;
		int* array_ofys;
	
public:
	iregpoly(int, int*,int*, GfxInfo shapeGfxInfo);

	virtual ~iregpoly();

	virtual void Draw(GUI* pUI) const;

	/////////
	virtual bool HitBox(int, int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);
	virtual void Save(ofstream& outfile)const override;
	virtual void Resize(double sacling_factor) {};
	virtual void ResizebyDrag(int, int) {}


	shape* Clone();


	virtual void Move(int x, int y) override {}

	
	
					
	virtual void getXlimits(int&, int&) {}; // used in multi move
	virtual void getYlimits(int&, int&) {}; // used in multi move
	virtual void relative_move(int x1, int y1, int x2, int y2) {};       //used in multimove
};
