#pragma once

#include "shape.h"

class Oval : public shape
{
private:
	Point Radius1,Radius2,Center;
	int radiusX, radiusY;
	
public:
	Oval(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Oval();
	virtual void Draw(GUI* pUI) const;
	virtual bool HitBox(int, int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);
	virtual void Save(ofstream& outfile)const override;
	virtual void Move(int x, int y) ;
	shape* Clone();



	virtual void Resize(double scaling_factor)   ;

	void getXlimits(int&, int&) ;   // used in multi move
	void getYlimits(int&, int&) ; // used in multi move
	virtual void relative_move(int x1, int y1, int x2, int y2) ;    //used in multi move
};

#pragma once
