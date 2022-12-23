#pragma once

#include "shape.h"

class Oval : public shape
{
private:
	Point Radius1;
	Point Radius2;
public:
	Oval(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Oval();
	virtual void Draw(GUI* pUI) const;
	virtual bool HitBox(int, int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);
	virtual void Save(ofstream& outfile)const override;

	shape* Clone();
};

#pragma once
