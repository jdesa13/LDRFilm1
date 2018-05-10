#include <cstdint>(stdint.h)
#pragma once
#ifndef _J_CORE
#define _J_CORE

class create {
protected: 
	uint8_t *pixel;
	double r, g, b;

public:
	create() {};
	create(double r, double g, double b); // inputs are gonna need to be between 0 - 1 
	~create() {};

	uint8_t* core(int width, int height);
};

#endif