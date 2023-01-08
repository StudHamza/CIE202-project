#include "opScramble.h"
#include "controller.h"
#include "GUI/GUI.h"




opScramble::opScramble(controller* pcont) :operation(pcont) {

}

opScramble::~opScramble()
{}


void opScramble::Execute() {	
	
	GUI* pUI = pControl->GetUI();



Graph* ptG = pControl->getGraph();


	string Fhide;

	pUI->PrintMessage("do you want to hide the shapes after scrambling them");
	Fhide=pUI->GetSrting();
	
	
	
	
	Point Grid[4][4];

	int width = pUI->getwidth();
	int height = pUI->getheight();

	int x = width / 4;
	int y = (height-50) / 4;    // -50 for the status bar
	/// <summary>
	/// creating 4*4 grid of maximum 16 positions(cards)
	/// </summary>

	for (int i = 0; i <= 3; i++) {

		for (int j = 0; j <= 3; j++) {
			int maxx = 50 + (x * (j + 1));    //+50 for Vtoolbar
			int minx = width - (4 - j) * x;
			Grid[i][j].x= abs((maxx + minx)) / 2;
			int maxy = 50 + (y * (i + 1));     //+50 for the toolbar height
			int miny = height - ((4 - i) * y);
			Grid[i][j].y = abs((maxy + miny)) / 2;

				
			
		}



	}















	ptG->random_move(Grid,Fhide);

	pUI->PrintMessage("Shapes has been scrambled ");




}
