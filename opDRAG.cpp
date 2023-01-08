#include "opDRAG.h"
#include "controller.h"
#include "GUI/GUI.h"




opDRAG::opDRAG(controller* pcont) :operation(pcont) {

}

opDRAG::~opDRAG()
{}

void opDRAG::Undo()
{
	shape* temp = pControl->getOperatedOn();
	Point Move = temp->GetPevPoint();
	cout << Move.x << " " << Move.y<<"Im in undo drag"<<endl;
	temp->Move(Move.x, Move.y);
}

void opDRAG::Execute() {

	GUI* pUI = pControl->GetUI();
	Graph* ptG = pControl->getGraph();


	/*shape* selectedshsape = ptG->GetSelectedShape();*/


	int x;
	int y;
	int xN = 0;
	int yN = 0;
	bool flag = false;

	/*	pUI->GetPointClicked(x, y);*/

	pUI->PrintMessage("hold on to a shape to drag it::to get out of dragging mode click on an empty space");




	shape* clickedshape;

	while (!flag) {
		if (pUI->GetButtonState(LEFT_BUTTON, xN, yN) == BUTTON_DOWN) {
			clickedshape = ptG->Getshape(xN, yN);
			if (clickedshape)
			{
				Point P_intial = { xN,yN };
				clickedshape->setPevPoint(P_intial);
				pControl->pushToOperatedOn(clickedshape);
				while (!flag)

				{
					pUI->PrintMessage("MOVING::hold on to  the new destination");
					clickedshape->Move(xN, yN);

					ptG->Draw(pUI);
					pUI->updatebuffer();


					if (pUI->GetButtonState(LEFT_BUTTON, xN, yN) == BUTTON_UP) {
						pUI->PrintMessage("shape has been dragged succesfully::to drag another shape hold  it::to get out of dragging mode click on an empty space");
						break;
					}

				}
			}
			else {
				pUI->PrintMessage("no shape was selected::escaping...");
				break;
			};




		};


	}

}
