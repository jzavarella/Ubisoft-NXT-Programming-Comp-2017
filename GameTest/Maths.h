/*
//The Maths class is a static class that I use to store all of my commonly used math functions
*/

#pragma once
class Maths
{
#define PI 3.14159265359
public:
	/*
	//Random() generates a number between the passed values (inclusive on both ends)
	*/
	static float Random(float lowerBound, float upperBound);
	/*
	//RotateX() returns the rotated x position of a vertex given the original x, y and the desired rotation angle in degrees
	*/
	static float RotateX(float X, float Y, float Angle);
	/*
	//RotateX() returns the rotated x position of a vertex given the original x, y and the desired rotation angle in degrees
	*/
	static float RotateY(float X, float Y, float Angle);
	/*
	//Radians() returns the passed in angle(degrees) converted to radians
	*/
	static float Radians(float degrees);
	/*
	//Distance() returns the distance between two points p1, and p2
	*/
	static float Distance(float p1x, float p1y, float p2x, float p2y);
};

