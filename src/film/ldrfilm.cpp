#include "Gregar_v.01/ldrfilm.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"



ldrfilm::ldrfilm() {
	mFormat = 0; mWidth = 800; mHeight = 600; 
}

ldrfilm::ldrfilm(int weigth, int height, unsigned int type){ 
	mFormat = type;  mWidth = weigth; mHeight = height; 
}

ldrfilm::~ldrfilm() {}


	void ldrfilm::save(const std::string &filename, float *ptr)
	{



		switch(mFormat) {
			 case 0 :
				 stbi_write_png(filename.c_str(), mWidth, mHeight, 4, ptr, mWidth * 4);
			 break;
			 case 1:
				 stbi_write_bmp(filename.c_str(), mWidth, mHeight, 4, ptr);
			 break;
			 case 2:
				 stbi_write_jpg(filename.c_str(), mWidth, mHeight,4,ptr,50);
			 break;
			 default:
			 std::cout<<"ERROR: - YOU MESSED UP - Image did not write properly"<<std::endl;
			}


	}

	int ldrfilm::GetFormat()
	{
		return mFormat;
	}

	void ldrfilm::SetFormat(int type)
	{
		mFormat = type;
	}