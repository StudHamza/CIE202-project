#pragma once

#include "Shape.h"
#include <vector>

class RegPoly : public shape
{
private:
	Point Center;
	Point Start;
	vector<int> Xv;
	vector <int> Yv;
	int Side;
public:
	RegPoly(Point, Point,int,GfxInfo shapeGfxInfo);
	void SetVertices();
	virtual void Draw(GUI* pUI) const;
	virtual ~RegPoly();
};

