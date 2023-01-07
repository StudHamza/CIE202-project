#include "controller.h"
#include "operations\opAddRect.h"
#include "operations\opAddRegPoly.h"
#include "operations\opSelect.h"
#include "operations\opSave.h"
#include "operations\opLoad.h"
#include "operations\opClear.h"
#include "operations\opExit.h"
#include "operations\opCOPY.h"
#include "operations\opPaste.h"
#include "operations\opAddCircle.h"
#include "operations\opAddTriangle.h"
#include "operations\opAddLine.h"
#include "operations\opAddOval.h"
#include "operations\opAddImage.h"
#include "operations\opCut.h"
#include "operations\opColors.h"
#include "operations\opChngDraw.h"
#include "operations\opChngFill.h"
#include "operations\opUndo.h"
#include"opScramble.h"
#include"opMultiMove.h"
#include"opDelete.h"
#include"opDRAG.h"
#include"opRESIZE.h"
//Constructor
controller::controller()
{
	pGraph = new Graph;
	pGUI = new GUI;	//Create GUI object
}

//==================================================================================//
//								operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation() const
{

	//Ask the input to get the operation from the user.

	return pGUI->GetUseroperation();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an operation and executes it
operation* controller::createOperation(operationType OpType)
{
	operation* pOp = nullptr;


	//According to operation Type, create the corresponding operation object
	switch (OpType)
	{
	case DRAW_RECT:
		pOp = new opAddRect(this);
		break;

	case DRAW_LINE:
		pOp = new opAddLine(this);

		break;
	case DRAW_CIRC:
		pOp = new opAddCircle(this);
		break;
	case DRAW_OVAL:
		pOp = new opAddOval(this);
		break;
	case DRAW_TRI:
		pOp = new opAddTriangle(this);
		break;
	case DRAW_REGPOLY:
		pOp = new opAddRegPoly(this);
		break;
	case CHNG_DRAW_CLR:
		pOp = new opChngDraw(this);
		break;
	case CHNG_FILL_CLR:
		pOp = new opChngFill(this);
		break;
	case COLOR_PALETTE:
		pOp = new opColors(this);
		break;
	case UNDO:
		pOp = new opUndo(this);
		break;
	case REDO:
		break;

	case SCRAMBLE:
		
		pOp = new opScramble(this);
		break;

	case DRAG:
		pOp = new opDRAG(this);
		break;
	case RESIZE:
		pOp = new opRESIZE(this);
		break;
	case MULTIMOVE:
		pOp = new opMultiMove(this);
		break;
	case SELECT_SHAPE:
		pOp = new opSelect(this);
		break;
	case DRAWING_AREA:
		//Unselect Selected Shapes
		pGraph->UnselectShape();
		pGUI->ClearStatusBar();
		break;
	case SAVE:
		pOp = new opSave(this);
		break;
	case LOAD:
		pOp = new opLoad(this);
		break;
	case COPY:
		pOp = new opCopy(this);
		break;
	case PASTE:
		pOp = new opPaste(this);
		break;
	case CUT:
		pOp = new opCut(this);
		break;
	case CLEAR:
		pOp = new opClear(this);
		break;
	case POST_IMAGE:
		pOp = new opAddImage(this);
		break;
	case EXIT:
		pOp = new opExit(this);
		///create Exitoperation here
		break;
	case DEL:
		pOp = new opDelete(this);
		break;
	case STATUS:	//a click on the status bar ==> no operation
		break;
	}

	return pOp;

}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all shapes on the user interface
void controller::UpdateInterface() const
{
	pGraph->Draw(pGUI);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the UI
GUI* controller::GetUI() const
{
	return pGUI;
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the Graph
Graph* controller::getGraph() const
{
	return pGraph;
}



//Destructor
controller::~controller()
{
	delete pGUI;
	delete pGraph;

}


//Time line related Functions-----------------------------------------------------------------------------------
operation* controller::UpdateTimeLine()
{
	operation* op = Present.back();	//get last element
	Present.pop_back();	//remove
	future.push_back(op); //Add
	return op;
}

void controller::pushToOperatedOn(shape* shp) { OperatedOn.push_back(shp); }

shape* controller::getOperatedOn() { if (OperatedOn.size()) { return OperatedOn.back(); } }


bool controller::checkPresent() { return Present.size(); }


void controller::UpdateDelete(shape* shp) { Deleted.push_back(shp); }

void controller::popOperatedOn()
{
	OperatedOn.pop_back();
}

void controller::DeleteTimeLine()
{
	operation* op = Present.back();	//get last element
	Present.pop_back();	//remove
	delete op;
}
/////////////-------------------------------------------------------------------------------------------





//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run()
{
	operationType OpType;
	do
	{
		//1. Ask the GUI to read the required operation from the user
		OpType = GetUseroperation();

		//2. Create an operation coresspondingly
		operation* pOpr = createOperation(OpType);

		//3. Execute the created operation
		if (pOpr)
		{
			char del = 'y';	//Create a char for not deleting/deallocating the pOpr 
			for (auto& Op : revertable)
			{
				if (OpType == Op)
				{
					del = 'n';
				}
			}
			pOpr->Execute();//Execute
			if (del != 'y') {
				Present.push_back(pOpr);//Sets the present timeline for undo/redo
				pOpr = nullptr;	//do not delete the pointer (not memeory leak)
			}
			else {
				delete pOpr;	//operation is not needed any more ==> delete it
				pOpr = nullptr;
			}
		}

		//Update the interface
		UpdateInterface();

		//3. Update present vector
	} while (OpType != ON_GOING);

}