#include <string>
#include <iostream>

#pragma once
#ifndef _J_FILM
#define _J_FILM

class film {

protected:
	film();
	film(int width, int height);
	~film() {};

	unsigned int width, height;

public:

	virtual void save(const std::string &filename, float *ptr) = 0;

};

#endif // _J_FILM