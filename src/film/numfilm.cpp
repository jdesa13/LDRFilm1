#include "Gregar_v.01/numfilm.h"

nfilm::nfilm()
	:film(800,600){}

nfilm::nfilm(const unsigned int width, const unsigned int height)
	:film(width, height){}

nfilm::~nfilm() {}

void nfilm::save(const std::string &filename, float *ptr)
{
	std::cout << "Writing a " << mWidth << "x" << mHeight << " NPZ file to \"" << filename << "\"" << std::endl;

	cnpy::npz_save(filename.c_str(), "radiances", (uint8_t *)ptr, {mHeight, mWidth, 4 }, "w");
}