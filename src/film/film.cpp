#include "Gregar_v.01/film.h"
#include "stb_image_write.h"
#include "stb_image.h"

void film::save(const std::string &filename, float *ptr) {

	stbi_write_png(filename.c_str(),width,height,4,ptr,width*4);

}