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


		//Scale and cast for bitmap color range.
		uint8_t *pixels = new uint8_t[mWidth * mHeight * 4];

		unsigned int index = 0;
		for (int rows = 0; rows<mHeight; rows++)
			for (int cols = 0; cols < mWidth; cols++)
			{
				index = rows*mWidth * 4 + cols * 4;
				pixels[index + 0] = 255 * ptr[index + 0];
				pixels[index + 1] = 255 * ptr[index + 1];
				pixels[index + 2] = 255 * ptr[index + 2];
				pixels[index + 3] = 255 * ptr[index + 3];
			}


		switch(mFormat) {
			 case 0 :
				 stbi_write_png(filename.c_str(), mWidth, mHeight, 4, pixels, mWidth * 4);
			 break;
			 case 1:
				 stbi_write_bmp(filename.c_str(), mWidth, mHeight, 4, pixels);
			 break;
			 case 2:
				 stbi_write_jpg(filename.c_str(), mWidth, mHeight,4, pixels,100);
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