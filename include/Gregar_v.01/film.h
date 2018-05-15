#include <string>
#include <iostream>

#pragma once
#ifndef _J_FILM
#define _J_FILM

class film {
protected:
	unsigned int mWidth, mHeight;

	film() {};
	film(int width, int height)
		: mWidth(width), mHeight(height) {};
	~film() {};
	//void save(const std::string &filename, float *ptr);

public:


	virtual void save(const std::string &filename, float *ptr) = 0;

};

#endif // _J_FILM