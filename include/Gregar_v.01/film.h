#include<string>
#pragma once
#ifndef _J_FILM
#define _J_FILM

class film {

protected:
	unsigned int width, height;

public:
	film();
	film(int width, int height);
	~film() {};

	void save(std::string filename, float *ptr);

};

#endif // _J_FILM