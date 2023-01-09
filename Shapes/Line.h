#pragma once

#include "shape.h"

class Line : public shape
{
private:
	Point Start;
	Point End;
	double Distance;

	Point midpoint;
public:
	Line(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
	virtual bool HitBox(int, int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);
	virtual void Save(ofstream& outfile)const override;
	virtual void Move(int x, int y) override;

	shape* Clone() override;


	virtual void Resize(double sacling_factor) override;
	virtual void ResizebyDrag(int,int) override;

	void getXlimits(int&, int&) override;   // used in multi move
	void getYlimits(int&, int&) override; // used in multi move
	virtual void relative_move(int x1, int y1, int x2, int y2) override;
	virtual void Draw_iamge(GUI* pUI) {};
};

#pragma once
