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
	virtual void Save(ofstream& outfile)const override;
	virtual void Move(int x, int y) override;

	shape* Clone();

	 void getXlimits(int&,int&)   override;   // used in multi move
	 void getYlimits(int&,int&) override; // used in multi move
	 virtual void relative_move(int x1, int y1, int x2, int y2) override;

	
};
