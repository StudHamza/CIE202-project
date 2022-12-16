#pragma once

#include "shape.h"

class Triangle : public shape
{
private:
	Point F, S, T;
public:
	Triangle(Point, Point,Point ,GfxInfo shapeGfxInfo);
	virtual ~Triangle();
	virtual void Draw(GUI* pUI) const;
	virtual bool HitBox(int, int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);
	virtual void Save(ofstream& outfile)const override;

	shape* Clone();
};
