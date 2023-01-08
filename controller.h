#pragma once

#include "DEFS.h"
#include "Shapes\Graph.h"
#include "GUI\GUI.h"

class operation; //forward declaration

//Main class that manages everything in the application.
class controller
{

	Graph* pGraph;	//pointe to the grapg
	GUI* pGUI;	//Pointer to UI class
	int revertable[11]={ DRAW_LINE,DRAW_RECT,DRAW_TRI,DRAW_CIRC,DRAW_OVAL,DRAW_REGPOLY,CHNG_DRAW_CLR,
		CHNG_FILL_CLR,RESIZE,DEL,DRAG};
	vector<operation*>Present;	
	vector<operation*>future;
	vector<shape*>OperatedOn;
	vector<shape*>FutureOperatedOn;
public:	
	controller(); 
	~controller();
	
	// -- operation-Related Functions
	//Reads the input command from the user and returns the corresponding operation type
	operationType GetUseroperation() const;
	operation* createOperation(operationType) ; //Creates an operation



////////////////////////////////////////////////////////////////////////////////////////////////
	operation* UpdateTimeLine();	//1. Gets the latest op 2.Removes it from present 3.Adds it to future

	void pushToOperatedOn(shape* shp);	//All shapes that are changed

	void popOperatedOn();//pops last element/shape out

	shape* getOperatedOn();	//gets recent shape


	bool checkPresent(); //tells whether the vector is empty or not

	/////////////////Future/////////

	void pushToFutureOperatedOn(shape*); //Vector to store undone operations

	shape* getFutureOperatedOn();

	bool checkFuture();		//checks if size of vector>0

	

	operation* UpdateFuture();	//Removes last op from Future and pushes it to present

	void popOperatedOnToPresent();		//returns undone to present timeline


	/////////////////             Special cases                   ///////////////////////////////////////////////
	void DeleteTimeLine();	//Some times op is saved but not revesable since im following DRY: ex Fill/DrawColor
	
	void clearFuture();


	void Run();
	
	Graph* getGraph() const;
	
	// -- Interface Management Functions
	GUI *GetUI() const; //Return pointer to the UI
	void UpdateInterface() const;	//Redraws all the drawing window	

};

