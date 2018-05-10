#include "film.h"

#pragma once
#ifndef _J_LDRFILM
#define _J_LDRFILM
class ldrfilm : public film {
protected:
	unsigned int format;

public:
	ldrfilm();
	ldrfilm(int weigth, int height, enum type);
	~ldrfilm() {};

	void save(std::string filename, float *ptr);
	int GetFormat();
	void SetFormat(int type);
};

#endif