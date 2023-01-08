#include "opResizebyDrag.h"
#include "controller.h"

#include "GUI/GUI.h"
#include <iostream>

opResizebyDrag::opResizebyDrag(controller* pCont) : operation(pCont) {}

opResizebyDrag::~opResizebyDrag() {
}



void opResizebyDrag::Execute()
{

	GUI* pUI = pControl->GetUI();
	Graph* ptG = pControl->getGraph();

	int x;
	int y;
	int xN = 0;
	int yN = 0;
	bool flag = false;





	/*	pUI->GetPointClicked(x, y);*/


	pUI->PrintMessage("hold on to a shape to resize and rotate ::to get out of dragging mode click on an empty space");

	shape* clickedshape;

	while (!flag) {
		if (pUI->GetButtonState(LEFT_BUTTON, xN, yN) == BUTTON_DOWN) {

			clickedshape = ptG->Getshape(xN, yN);
			if (clickedshape)
				while (!flag)

				{


					pUI->PrintMessage("RESIZING::");
					clickedshape->ResizebyDrag(xN, yN);

					ptG->Draw(pUI);
					pUI->updatebuffer();


					if (pUI->GetButtonState(LEFT_BUTTON, xN, yN) == BUTTON_UP) {
						pUI->PrintMessage("to Resize or rotate another shape by dragging hold on to it ::to get out of dragging mode click on an empty space");
						break;
					}

				}
			else {
				pUI->PrintMessage("no shape was selected::escaping...");
				break;
			};




		};


	}








}