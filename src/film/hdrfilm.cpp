#include "Gregar_v.01/hdrfilm.h"

hdrfilm::hdrfilm()
:film(800,600){}

hdrfilm::hdrfilm(const unsigned int width, const unsigned int height)
:film(width,height){}

hdrfilm::~hdrfilm()
{}

void hdrfilm::save(const std::string &filename, float *ptr){

	Imf::Header header(mWidth,mHeight);
	header.channels().insert("R", Imf::Channel(IMF::FLOAT));
	header.channels().insert("G", Imf::Channel(IMF::FLOAT));
	header.channels().insert("B", Imf::Channel(IMF::FLOAT));

	Imf::OutputFile file(filename.c_str(),header);

	Imf::FrameBuffer frameBuffer;

	size_t strides = sizeof(float);
	size_t pStride = 4 * strides;
    size_t rStride = pStride * (int)mWidth;

	char* castptr = reinterpret_cast<char *>(ptr);

	frameBuffer.insert("R", Imf::Slice(IMF::FLOAT, castptr, pStride, rStride));
	castptr += strides;
	frameBuffer.insert("G", Imf::Slice(IMF::FLOAT, castptr, pStride, rStride));
	castptr += strides;
	frameBuffer.insert("B", Imf::Slice(IMF::FLOAT, castptr, pStride, rStride));

	file.setFrameBuffer(frameBuffer);
	file.writePixels(mHeight);

}