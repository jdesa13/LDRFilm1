#pragma once
#ifndef _J_CORE
#define _J_CORE

#include <iostream>

#include <stdint.h>
#include "Gregar_v.01/create.h"
#define BITMAPRANGE 255



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