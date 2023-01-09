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
	int Radius;
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


	virtual void Resize(double sacling_factor) override;
	virtual void ResizebyDrag(int, int);


	shape* Clone();		 //Clone shape into new object

	void getXlimits(int&, int&) ;   // used in multi move
	void getYlimits(int&, int&) ; // used in multi move
	virtual void relative_move(int x1, int y1, int x2, int y2) ;


	virtual void Move(int x, int y) override {


		
		int dx;
		int dy;
		int dx2;
		int dy2;
		
		
		dx = abs(Center.x - x);
		dy = abs(Center.y - y);



		dx2 = abs( Start.x-x);
		dy2 = abs( Start.y-y);

		


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


		if (y >= Start.y) {

		
			this->Start.y += dy2;
		}
		else
		{
		
			this->Start.y -= dy2;


		}
		if (x >= Start.x)
			this->Start.x += dx2;
			
		else
			this->Start.x -= dx2;



		Radius = sqrt(pow((Center.x - Start.x), 2) + pow((Center.y - Start.y), 2));




	}

	virtual void Draw_iamge(GUI* pUI) {};
};







