#pragma once
#include "..\defs.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <iostream>

//Base class for all shapes
class shape
{
protected:
	int ID;		//Each shape has an ID
	GfxInfo ShpGfxInfo;	//shape graphis info
	static int counter;
	image sticked;
	/// Add more parameters if needed.

public:

	shape(GfxInfo shapeGfxInfo);
	virtual ~shape() {}
	virtual shape* Clone() = 0;		//Copy constructor that'll be virtual
	void SetSelected(bool s);	//select/unselect the shape
	bool IsSelected() const;	//check whether fig is selected
	

	virtual void Draw(GUI* pUI) const =0 ;		//Draw the shape
	virtual bool HitBox(int,int)const =0;		//create hit box

	//Colors//
	void ChngDrawClr(color Dclr);	//changes the shape's drawing color
	void ChngFillClr(color Fclr);	//changes the shape's filling color
	//Getters
	color GetCrntColor()const;
	color getPevDrawClr()const;

	//setters
	void SetFill(bool);		//Sets fill to true or false
	void setPevDrawColors();	//vector of pev draw colors
	void setPevFillColors();	//vector of pev fill colors
	void setPevFillBool();

	//Hybrid Getters and setters
	color UpdatePevDrawClr();
	color UpdatePevFillClr();


	//Selecting//
	void Selected(color);
	void UnSelect();
	void UpdateId();		//resposible for id updates when cloning(copy paste)
	///The following functions should be supported by the shape class
	///It should be overridden by each inherited shape
	virtual string GetInfo(char)const = 0;		//Return a string of all shape info. Is used in save and select functiosn
	///Decide the parameters that you should pass to each function	
	bool IsSaved();
	void SetSaved(bool s);



	//Images
	void stickImage(image);

	//Moving
	virtual void Shift(int, int)=0;

	//Virtual save 
	virtual void Save(ofstream &outfile)const=0;


	//virtual void Rotate() = 0;	//Rotate the shape
	//virtual void Resize() = 0;	//Resize the shape
	virtual void Move(int x, int y) = 0;				//Move the shape
	virtual void getXlimits(int&,int&) = 0; // used in multi move
	virtual void getYlimits(int&,int&) = 0; // used in multi move
	virtual void relative_move(int x1,int y1 ,int x2,int y2) = 0;       //used in multimove

};
