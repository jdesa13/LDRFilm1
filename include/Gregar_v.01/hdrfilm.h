

#include "film.h"
#include <complex>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "OpenEXR/IlmImf/ImfFrameBuffer.h"
#include "OpenEXR/IlmImf/ImfHeader.h"
#include "OpenEXR/IlmImf/ImfOutputFile.h"
#include "OpenEXR/IlmImf/ImfChannelList.h"
#include "OpenEXR/IlmImfExamples/drawImage.h"

#pragma once
#ifndef _J_HDRFILM
#define _J_HDRFILM
class hdrfilm : public film {
public:
	hdrfilm();
	hdrfilm(const unsigned int width, const unsigned int height);
	~hdrfilm();
	virtual void save(const std::string &filename, float *ptr);

};
#endif