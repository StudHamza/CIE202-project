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
	Image.open(path);
	if (Image) {

		image Stick(path);
		if ((Stick.GetHeight() || Stick.GetWidth()) > 800) {
			pUI->PrintMessage("Image is way too Large, reduce it dimensions");
		}
		else {
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
			Image.close();
		}
	}
	else
	{
		pUI->PrintMessage("Path does not exist");
	}
}