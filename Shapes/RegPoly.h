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


	virtual void Move(int x, int y) override {



		int dx;
		int dy;

		dx = abs(Center.x - x);
		dy = abs(Center.y - y);


		for (int i = 0; i < Side; i++) {
			if (x > Center.x)
				Xv[i] += dx;
			else
				Xv[i] -= dx;
		}


		for (int i = 0; i < Side; i++) {
			if (y > Center.y)

				Yv[i] += dy;
			else
				Yv[i] -= dy;


		}

		Center.x = x;
		Center.y = y;




	}


};







