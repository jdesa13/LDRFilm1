#include <iostream>
#include <cstdint>(stdint.h)
#include "..\..\include\Gregar_v.01\create.h"
#define BITMAPRANGE 255

create::create(double r, double g, double b)
{
	
}

uint8_t* create ::core(int w, int h) {

	int size = w * h * 4;

	pixel = new uint8_t[size];
	if (pixel == NULL)
	{
		std::cout << "Failed to allocate memory" << std::endl;
	}


	unsigned int index = 0;
	for (int rows = 0; rows<h; rows++)
		for (int cols = 0; cols < w; cols++)
		{
			index = rows * w * 4 + cols * 4;
			pixel[index + 0] = BITMAPRANGE * r; //Red
			pixel[index + 1] = BITMAPRANGE * g; //Green
			pixel[index + 2] = BITMAPRANGE * b; //Blue
			pixel[index + 3] = BITMAPRANGE * 1; // Alpha
		}

	return pixel;
}

