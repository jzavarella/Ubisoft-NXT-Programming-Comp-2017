#include "stdafx.h"
#include "Maths.h"
#include <random>
#include <math.h>

float Maths::Random(float lowerBound, float upperBound) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(lowerBound, upperBound); // define the range

	return distr(eng);
}

float Maths::RotateX(float X, float Y, float Angle) {
	return X*cosf(Angle*PI / 180) - Y*sinf(Radians(Angle));
}
float Maths::RotateY(float X, float Y, float Angle) {
	return Y*cosf(Angle*PI / 180) + X*sinf(Radians(Angle));
}

float Maths::Radians(float degrees) {
	return degrees * PI / 180;
}

float Maths::Distance(float p1x, float p1y, float p2x, float p2y) {
	return sqrtf(pow(p2x - p1x, 2) + pow(p2y - p1y, 2));
}