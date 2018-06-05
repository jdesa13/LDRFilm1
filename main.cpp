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

Eigen::Vector3d A(-1, 1, -2);
Eigen::Vector3d B(1, 1, -2);
Eigen::Vector3d C(0, -1, -2);
Eigen::Vector3d tri[3] = { A,B,C };

Eigen::Vector3d dr(0, 0, -1);
Eigen::Vector3d P(0, 0, 0);

Eigen::Vector3d R(-2, 1, -3);
Eigen::Vector3d E(2, 1, -3);
Eigen::Vector3d D(1, -1, -3);
Eigen::Vector3d red[3] = { R,E,D };

Eigen::Vector3d Q;

int theta = 66;

float tNearest = INFINITY;
/////////////////////////////////////
Eigen::Vector3d pt(0,0,-1);
Eigen::Vector3d cen(0,0,-4);
int radius = -2;

int hit = 1;
int miss = 0;

int width = 800;
int height = 600;

Eigen::Vector3d circletest(Eigen::Vector3d origin,Eigen::Vector3d dr, Eigen::Vector3d cen, int r) {

	int rad = pow(r,2);
	float Xo, Yo, Zo, Xd, Yd, Zd, Xc, Yc, Zc;
	float t;

	Xo = origin(0);
	Yo = origin(1);
	Zo = origin(2);

	Xd = dr(0);
	Yd = dr(1);
	Zd = dr(2);

	Xc = cen(0);
	Yc = cen(1);
	Zc = cen(2);
	
	float a = pow(Xd, 2) + pow(Yd, 2) + pow(Zd, 2);
	float b = 2 * (((Xo*Xd)-(Xd*Xc))+ ((Yo*Yd) - (Yd*Yc))+ ((Zo*Zd) - (Zd*Zc)));
	float c = (pow(Xo, 2) + pow(Xc, 2) - (2 * Xo*Xc))+ (pow(Yo, 2) + pow(Yc, 2) - (2 * Yo*Yc))+ (pow(Zo, 2) + pow(Zc, 2) - (2 *Zo*Zc))-rad;
	
	float D = pow(b, 2) - (4 * a * c);

	if (D == 0) {
		t = -b / 2;
	}
	else if (D > 0) {
		float t0 = (-b - pow(D, (1 / 2))) / (a * 2);
		float t1 = (-b + pow(D, (1 / 2))) / (a * 2);
		if (t0 > 0) {
			t = t0;
		}
		else
			t = t1;
	}
	else
	{
		return origin; 
	}

	Eigen::Vector3d p = origin + dr * t;

	return p;
}

int intersectiontest(Eigen::Vector3d p, Eigen::Vector3d dr, Eigen::Vector3d triangle[]) {

	Eigen::Vector3d BA = triangle[1] - triangle[0];
	Eigen::Vector3d CA = triangle[2] - triangle[0];
	Eigen::Vector3d ABC = BA.cross(CA);
	float CBA = ABC.norm();

	Eigen::Vector3d normal = ABC / CBA;

	float d = normal.dot(triangle[0]);

	float t = (d - (normal.dot(p)))/(normal.dot(dr));

	Q = P + (t*dr);

	float check1 = ((triangle[1] - triangle[0]).cross(Q - triangle[0])).dot(normal);
	float check2 = ((triangle[2] - triangle[1]).cross(Q - triangle[1])).dot(normal);
	float check3 = ((triangle[0] - triangle[2]).cross(Q - triangle[2])).dot(normal);

	if (check1 >= 0 && check2 >= 0 && check3 >= 0)
	{
		return hit;
	}
	else
		return miss;
}

float intersectionloc(Eigen::Vector3d p, Eigen::Vector3d dr, Eigen::Vector3d triangle[]) {

	int hit = 1;
	int miss = 0;

	Eigen::Vector3d BA = triangle[1] - triangle[0];
	Eigen::Vector3d CA = triangle[2] - triangle[0];
	Eigen::Vector3d ABC = BA.cross(CA);
	float CBA = ABC.norm();

	Eigen::Vector3d normal = ABC / CBA;

	float d = normal.dot(triangle[0]);

	float t = (d - (normal.dot(p))) / (normal.dot(dr));

	return t;
}

Eigen::Vector3d shade(Eigen::Vector3d origin, Eigen::Vector3d sect, float Kd, float Ks, float Ka, Eigen::Vector3d Scol, Eigen::Vector3d Lcol, Eigen::Vector3d Lpos, Eigen::Vector3d Sc) {

	Eigen::Vector3d Hitc;
	Eigen::Vector3d w (0,0,0);
	if (sect == origin) {
		Hitc = w;
	}
	else
	{
		Eigen::Vector3d rdl = (Lpos - sect);
		Eigen::Vector3d n = (sect - Sc);
		Eigen::Vector3d rdeye = sect - origin;
		Eigen::Vector3d Nnorm = n.normalized();
		Eigen::Vector3d Snorm = Scol.normalized();
		Eigen::Vector3d Lnorm = Lcol.normalized();

		float ldn = Nnorm.dot(rdl.normalized());

		if (ldn < 0) {
			ldn = 0;
		}

		//float LNpos = (Lpos.normalized()).dot(Nnorm);
		Eigen::Vector3d rp = (2 * ldn)*Nnorm - Lpos.normalized();
		float rpeye = rp.normalized().dot(rdeye.normalized());
		float shine = 50;
		float rdvn = pow(rpeye, shine);

		Eigen::Vector3d SLcol(Snorm(0)*Lnorm(0), Snorm(1)*Lnorm(1), Snorm(2)*Lnorm(2));

		Eigen::Vector3d Dc = Kd * SLcol.normalized() * ldn;
		Eigen::Vector3d Ac = Ka * SLcol.normalized() * Kd;
		Eigen::Vector3d EV = Ks * SLcol.normalized() * rdvn;

		Hitc = Dc + Ac + EV;
	}
	return Hitc;
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

			float Pcx = AR*(2 * ((j + .5) / width) - 1)*tan((theta/2)*PI/180);
			float Pcy = AR*(1 - 2 * ((i + .5) / height))*tan((theta / 2)*PI / 180);

			Eigen::Vector3d Pc(Pcx,Pcy,-1);
			Eigen::Vector3d Rd = Pc - P;

			float point = intersectiontest(P, Rd, tri);
			float points = intersectiontest(P, Rd, red);

			index = i * width * 4 + j * 4;
			if (point == hit && points == hit) {
				float r = intersectionloc(P, Rd, red);
				float w = intersectionloc(P, Rd, tri);

				if (r < tNearest && w < tNearest && w < r) {

					//std::cout << point << " ";

					pixel[index + 0] = point; //Red
					pixel[index + 1] = point; //Green
					pixel[index + 2] = point; //Blue
					pixel[index + 3] = 1.0; // Alpha
				}
				else {

					//std::cout << point << " ";

					pixel[index + 0] = points; //Red
					pixel[index + 1] = 0; //Green
					pixel[index + 2] = 0; //Blue
					pixel[index + 3] = 1.0; // Alpha

				}
			}
			else if (point == hit && points == miss) {
			
				pixel[index + 0] = point; //Red
				pixel[index + 1] = point; //Green
				pixel[index + 2] = point; //Blue
				pixel[index + 3] = 1.0; // Alpha

			}
			else if (point == miss && points == hit) {

				pixel[index + 0] = points; //Red
				pixel[index + 1] = 0; //Green
				pixel[index + 2] = 0; //Blue
				pixel[index + 3] = 1.0; // Alpha

			}
		}
		//std::cout << std::endl;
	}

	//test_ldr.save("A.png", pixel);
	//std::cout << "Here";

	//int point = intersectiontest(P,dr,tri);
////////////////////////////////////////////////////////////////////////////////////
	float *pix = new float[size];
	if (pix == NULL)
	{
		std::cout << "Failed to allocate memory" << std::endl;
	}

	//int mark = circletest(P,pt,cen,radius);
	//std::cout<< mark << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			float Pcx = AR * (2 * ((j + .5) / width) - 1)*tan((theta / 2)*PI / 180);
			float Pcy = AR * (1 - 2 * ((i + .5) / height))*tan((theta / 2)*PI / 180);

			Eigen::Vector3d Pc(Pcx, Pcy, -1);
			Eigen::Vector3d rd = Pc - P;

			Eigen::Vector3d mark = circletest(P, rd, cen, radius);

				//std::cout << mark << " ";
			
			float Kd = .8;
			float Ks = .1;
			float Ka = .2;
			Eigen::Vector3d rcol(1,0,0);
			Eigen::Vector3d lwcol(1,1,1);
			Eigen::Vector3d light(2,2,2);

			Eigen::Vector3d filler = shade(P,mark,Kd,Ks,Ka,rcol,lwcol,light,cen);
	
			    index = i * width * 4 + j * 4;
				
				pix[index + 0] = filler(0); //Red
				pix[index + 1] = filler(1); //Green
				pix[index + 2] = filler(2); //Blue
				pix[index + 3] = 1.0; // Alpha

		}
		//std::cout << std::endl;
	}

	test_ldr.save("A.png", pix);
	std::cout << "Here";
}

