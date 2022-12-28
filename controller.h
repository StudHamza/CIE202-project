#pragma once

#include "DEFS.h"
#include "Shapes\Graph.h"
#include "GUI\GUI.h"

class operation; //forward declaration

//Main class that manages everything in the application.
class controller
{

	Graph* pGraph;	//pointe to the grapg
	GUI* pGUI;		//Pointer to UI class
	vector<operation*>Present;	
	vector<operation*>future;
	vector<shape*>OperatedOn;

	
public:	
	controller(); 
	~controller();
	
	// -- operation-Related Functions
	//Reads the input command from the user and returns the corresponding operation type
	operationType GetUseroperation() const;
	operation* createOperation(operationType) ; //Creates an operation



	// puts operation to future, pops operation from back
	operation* UpdateTimeLine();	//1. Gets the latest op 2.Removes it from present 3.Adds it to future
	void pushToOperatedOn(shape* shp);	//All shapes that are changed

	void popOperatedOn();//pops last element/shape out

	shape* getOperatedOn();	//gets recent shape


	bool checkPresent(); //tells whether the vector is empty or not




	void Run();
	
	Graph* getGraph() const;
	
	// -- Interface Management Functions
	GUI *GetUI() const; //Return pointer to the UI
	void UpdateInterface() const;	//Redraws all the drawing window	

};

