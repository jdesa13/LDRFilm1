#include "Gregar_v.01/ldrfilm.h"
#include "stb_image_write.h"
#include "stb_image.h"


	void ldrfilm::save(const std::string filename, float *ptr)
	{
		switch(mFormat) {
			 case 0 :
				 stbi_write_png(filename.c_str(), width, height, 4, ptr, width * 4);
			 break;
			 case 1:
				 stbi_write_bmp(filename.c_str(), width, height, 4, ptr);
			 break;
			 case 2:
				 stbi_write_jpg(filename.c_str(),width,height,4,ptr,50);
			 break;
			 default:
			 std::cout<<"YOU MESSED UP"<<std::endl;
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