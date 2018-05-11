#include "Gregar_v.01/ldrfilm.h"



	void ldrfilm::save(const std::string filename, float *ptr)
	{
		/*switch(mFormat) {
			 case 0 :
			 //swrite it
			 break;
			 case 1:
			 // sdfsd
			 break;
			 default:
			 std::cout<<"YOU MESSED UP"<<std::endl;
			}

*/
	}

	int ldrfilm::GetFormat()
	{
		return mFormat;
	}

	void ldrfilm::SetFormat(int type)
	{
		mFormat = type;
	}