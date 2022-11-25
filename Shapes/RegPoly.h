#pragma once

#include "Shape.h"

class RegPoly : public shape
{
private:
	Point Center;
	Point Start;
	int Side;
public:
	RegPoly(Point, Point,int,GfxInfo shapeGfxInfo);
	virtual ~RegPoly();
	virtual void Draw(GUI* pUI) const;
};

