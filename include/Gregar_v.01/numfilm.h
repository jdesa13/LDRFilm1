#pragma once

#include "film.h"
#include "cnpy.h"


#include <complex>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#ifndef _J_NUMFILM
#define _J_NUMFILM
class nfilm : public film {
public:
	nfilm();
	nfilm(const unsigned int width, const unsigned int height);
	~nfilm();
	virtual void save(const std::string &filename, float *ptr);
};
#endif