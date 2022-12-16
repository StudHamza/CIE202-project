#pragma once

#include "shape.h"

class Line : public shape
{
private:
	Point Start;
	Point End;
	double Distance;
public:
	Line(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
	virtual bool HitBox(int, int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);
	virtual void Save(ofstream& outfile)const override;

	shape* Clone();
};

#pragma once
