#include "Gregar_v.01/film.h"
#include "Gregar_v.01/ldrfilm.h"
#include "Gregar_v.01/numfilm.h"
#include "Gregar_v.01/hdrfilm.h"
#include <iostream>
#include <stdint.h>

#define WIDTH 800
#define HEIGHT 600
#define BITMAPRANGE 255


int main(int argc, char** argv)
{
	ldrfilm test_ldr(WIDTH, HEIGHT,0);
	hdrfilm test_hdr(WIDTH, HEIGHT);
	nfilm test(WIDTH,HEIGHT);

	int size = WIDTH * HEIGHT * 4;

	float *pixel = new float[size];
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

	test_ldr.save("A.png", pixel);
	std::cout<<"Here";

	test_hdr.save("A.exr", pixel);
	std::cout << "Here";

	test.save("A.npz", pixel);
	std::cout << "Here";
	//elete red;
	
	return 0;
}