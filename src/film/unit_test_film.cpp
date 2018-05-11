#include "Gregar_v.01/film.h"
#include "Gregar_v.01/ldrfilm.h"
#include <iostream>
#include <stdint.h>
#define WIDTH 1024
#define HEIGHT 728
#define BITMAPRANGE 255


int main(int argc, char** argv)
{
	film *red = new film(WIDTH, HEIGHT);

	int size = WIDTH * HEIGHT * 4;

	uint8_t *pixel = new uint8_t[size];
	if (pixel == NULL)
	{
		std::cout << "Failed to allocate memory" << std::endl;
	}


    unsigned int index = 0;
	for (int rows = 0; rows<HEIGHT; rows++)
		for (int cols = 0; cols < WIDTH; cols++)
		{
			index = rows * WIDTH * 4 + cols * 4;
			pixel[index + 0] = BITMAPRANGE * 1; //Red
			pixel[index + 1] = BITMAPRANGE * 0; //Green
			pixel[index + 2] = BITMAPRANGE * 0; //Blue
			pixel[index + 3] = BITMAPRANGE * 1; // Alpha
		}

	red->save("A.png", (float*)pixel);

	delete red;
	
	return 0;
}