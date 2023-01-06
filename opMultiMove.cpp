#include "opMultiMove.h"

#include "controller.h"
#include "GUI/GUI.h"




opMultiMove::opMultiMove(controller* pcont) :operation(pcont) {

}

opMultiMove::~opMultiMove()
{}


void opMultiMove::Execute() {
	



	POINT centre_shapes;
	GUI* pUI = pControl->GetUI();
	Graph* ptG = pControl->getGraph();

	if (ptG->GetSelectedShape()) {
		int x, y;
		int maxX=0, minX=0;
		ptG->getshapeslimitsX(maxX, minX);
		int maxY=0, minY=0;
		ptG->getshapeslimitsY(maxY, minY);

		centre_shapes.x = abs((maxX + minX)) / 2;
		centre_shapes.y =abs (maxY + minY) / 2;
	


		pUI->PrintMessage("MultiMove::click on a point to move your gp of shapes");

		pUI->GetPointClicked(x, y);

		ptG->multimove(centre_shapes.x, centre_shapes.y, x, y);

		pUI->PrintMessage("shapes has been moved succesfully");
		
	
	
		ptG->getshapeslimitsX(maxX, minX);
		
		ptG->getshapeslimitsY(maxY, minY);

		centre_shapes.x = abs((maxX + minX)) / 2;
		centre_shapes.y = abs(maxY + minY) / 2;

		

	}
	if(!ptG->GetSelectedShape()) {
		pUI->PrintMessage("no shapes are selected to be moved");

	}
	


}
