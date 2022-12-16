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
	virtual bool HitBox(int,int)const;
	virtual string GetInfo(char)const;
	virtual void Shift(int,int);
	virtual void Save(ofstream& outfile)const override;

	virtual ~RegPoly();


	shape* Clone();		 //Clone shape into new object
};

