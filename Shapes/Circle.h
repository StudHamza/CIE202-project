#pragma once


#include "shape.h"

class Circle : public shape
{
private:
	Point Center;
	Point Start;
	int Radius;
public:
	Circle(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
	virtual bool HitBox(int, int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);

	shape* Clone();
};
