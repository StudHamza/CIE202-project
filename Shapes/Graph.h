#pragma once
#include "Shape.h"
#include "RegPoly.h"
#include "Rect.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"
#include "Oval.h"
#include <fstream>
#include <vector>


using namespace std;

//forward decl
class GUI;	

//A class that is responsible on everything related to shapes
class Graph
{
private:
	vector <shape*> shapesList; //a container to hold all shapes							   
	shape* selectedShape;	//pointer to the currently selected shape
	Point* pvp = new Point{0,0}; //isnt dellocated yet
	vector <shape*> clipboard;	//copy of selected shpes
public:										
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void Draw(GUI* pUI) const;			//Draw the graph (draw all shapes)

	//Select///////////////////--------------------------
	shape* Getshape(int x, int y) const; //Search for a shape given a point inside the shape
	string SelectShape(Point,color,shape *);	//Responsible for shape selection
	bool UnselectShape();	//Unselects if clicked on drawing area
	void UnSelectAll();
	shape* GetSelectedShape()const;
	vector<shape*> GetShapeList()const;
	void PopFromShapeList(shape*);
	void set_tonull() {
		 selectedShape= nullptr;

	}
	////////////////////////---------------------------
	//Copy and Paste and Cut//
	void ClipBoard();		//sets a vector of the selected shapes
	bool getClipBoard() const;
	void Paste();
	void delShape();         //delete and multi-delete
	void deleteSingleShape(shape*);
	void cut();




	void Save(ofstream& outfile,color,color,int);	//Save all shapes to a file
	void load(ifstream& inputfile);	//Load all shapes from a file

	bool Exit();		//Checks for saved shapes

	void Clear();
	void CheckSaved();


	
	/// <summary>
	/// scramble and multimove functions
	/// </summary>
	void random_move(Point Grid[][4]);      //used in scramble;
	void multimove(int x1, int y1, int x2, int y2);       //used in multimove


	void getshapeslimitsX(int&,int&);//useed in multimove
	void getshapeslimitsY(int&,int&);  //used in multimove

};
