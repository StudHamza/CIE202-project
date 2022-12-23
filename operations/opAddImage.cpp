#include "opAddImage.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"
#include <iostream>
#include <fstream>

opAddImage::opAddImage(controller* pCont) : operation(pCont) {}

opAddImage::~opAddImage() {
}



void opAddImage::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGph = pControl->getGraph();
	pUI->PrintMessage("Please write the exact file path");
	string path = pUI->GetSrting();
	fstream Image;
	Point P1={0,0}, P2={0,100};
	Image.open(path+".jpg");
	if (Image) {

		image Stick(path+ ".jpg");
		if ((Stick.GetHeight() || Stick.GetWidth()) > 1000) {
			pUI->PrintMessage("Image is way too Large, reduce it dimensions");
		}
		else {	// I need to make a box around each shape inorder to stick an image into it
			/*
			shape* Frame = pGph->GetSelectedShape();
			for (int i = 0; i < Stick.GetWidth(); i++)
			{
				for (int j = 0; j < Stick.GetHeight(); j++)
				{

					if (!(pGph->Getshape(i, j))) {
						pUI->FrameImage(Stick, i, j);
					}
				}
			}
			Frame->stickImage(Stick);
		}
		*/
			pUI->drawImage(Stick, {0,0}, {0,100});
			Image.close();
		}
	}
	else
	{
		pUI->PrintMessage("Path does not exist");
	}
}