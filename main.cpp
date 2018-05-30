#include<complex>
#include<cstdlib>
#include<iostream>
#include<map>
#include<string>
#include<Eigen/Dense>
#include <math.h>
#include "Gregar_v.01/film.h"
#include "Gregar_v.01/ldrfilm.h"
#define PI 3.14

Eigen::Vector3d A(2,1,1);
Eigen::Vector3d B(2, 0, -1);
Eigen::Vector3d C(2, -1, 1);

Eigen::Vector3d dr(1, 0, 0);
Eigen::Vector3d P(0, 0, 0);

Eigen::Vector3d tri[3] = { A,B,C };

int theta = 35;

int width = 800;
int height = 600;

int intersectiontest(Eigen::Vector3d p, Eigen::Vector3d dr, Eigen::Vector3d triangle[]) {

	int hit = 1;
	int miss = 0;

	Eigen::Vector3d BA = triangle[1] - triangle[0];
	Eigen::Vector3d CA = triangle[2] - triangle[0];
	Eigen::Vector3d ABC = BA.cross(CA);
	int CBA = ABC.norm();

	Eigen::Vector3d normal = ABC / CBA;

	int d = normal.dot(triangle[0]);

	int t = (d - (normal.dot(p)))/(normal.dot(dr));

	int check1 = ((triangle[1] - triangle[0]).cross(dr - triangle[0])).dot(normal);
	int check2 = ((triangle[2] - triangle[1]).cross(dr - triangle[1])).dot(normal);
	int check3 = ((triangle[0] - triangle[2]).cross(dr - triangle[2])).dot(normal);

	if (check1 >= 0 && check2 >= 0 && check3 >= 0)
	{
		return hit;
	}
	else
		return miss;
}

int main(int argc, char** argv)
{
	ldrfilm test_ldr(width, height, 0);

	int AR = width/height;
	unsigned int index = 0;

	int size = width * height * 4;

	float *pixel = new float[size];
	if (pixel == NULL)
	{
		std::cout << "Failed to allocate memory" << std::endl;
	}


	for (int i=0; i < height; i++){
		for (int j=0; j < width; j++){

			int Pcx = (AR*(2 * (j + .5 / width) - 1))*tan((theta/2)*PI/180);
			int Pcy = (AR*(1-(i + .5 / height)*2))*tan((theta / 2)*PI / 180);

			Eigen::Vector3d Pc(Pcx,Pcy,-1);
			Eigen::Vector3d Rd = Pc - P;

			int point = intersectiontest(P, Rd, tri);

			//std::cout << point << " ";

			index = i* width * 4 + j * 4;
			pixel[index + 0] = point; //Red
			pixel[index + 1] = point; //Green
			pixel[index + 2] = point; //Blue
			pixel[index + 3] = 1.0; // Alpha
		}
		//std::cout << std::endl;
	}

	test_ldr.save("A.png", pixel);
	std::cout << "Here";

	//int point = intersectiontest(P,dr,tri);
}