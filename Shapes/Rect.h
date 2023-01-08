#pragma once

#include "shape.h"

class Rect : public shape
{
private:
	Point Corner1;	
	Point Corner2;
	Point centeroid;
public:
	Rect(Point , Point, GfxInfo shapeGfxInfo );
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;
	virtual bool HitBox(int,int) const;
	virtual string GetInfo(char)const;
	virtual void Shift(int, int);		
	virtual void Save(ofstream& outfile)const override;

	shape* Clone();
	virtual void Resize(double sacling_factor);
	virtual void ResizebyDrag(int, int);
	virtual void Move(int x, int y) override;

	void getXlimits(int&, int&) ;   // used in multi move
	void getYlimits(int&, int&) ; // used in multi move
	virtual void relative_move(int x1, int y1, int x2, int y2) ;     //used in multimove
};

