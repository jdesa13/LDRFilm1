#include"Gregar_v.01/cnpy.h"
#include<complex>
#include<cstdlib>
#include<iostream>
#include<map>
#include<string>



int main(int argc, char** argv)
{
	int size = 32;
	
	//set random seed so that result is reproducible (for testing)
	srand(0);
	//create random data
	std::vector<std::complex<double>> data(size);
	for (int i = 0; i < size; i++) data[i] = std::complex<double>(rand(), rand());

	//save it to file
	cnpy::npy_save("arr1.npy", &data[0], { 2,4,4 }, "w");
}