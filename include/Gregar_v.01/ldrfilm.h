#include "film.h"

#pragma once
#ifndef _J_LDRFILM
#define _J_LDRFILM
class ldrfilm : public film {
protected:
	unsigned int mFormat;
	

public:

	ldrfilm();
	ldrfilm(int weigth, int height, unsigned int type);
	~ldrfilm();
	virtual void save(const std::string &filename, float *ptr);
	int GetFormat();
	void SetFormat(int type);
};

#endif