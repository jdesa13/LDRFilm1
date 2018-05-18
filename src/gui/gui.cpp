#include "..\..\include\Gregar_v.01\gui.h"

gui::gui()
{
	mWidth = 800; 
	mHeight = 600;
}

gui::gui(int width, int height)
{
	mWidth = width; 
	mHeight = height;
	nanogui::Screen(nanogui::Vector2i(mWidth,mHeight),"Test");
	
}

gui::~gui()
{}

