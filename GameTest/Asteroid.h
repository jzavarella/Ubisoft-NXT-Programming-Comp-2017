/*
//The asteroid class stores all of the variables and methods associated with drawing, moving, and generating asteroids
*/

#include <vector>
#include "Maths.h"

#pragma once
class Asteroid
{
public:
	/*
	//Constructor which sets the initial position, number of edges, radius, initial heading, initial velocity componets
	//and max speed
	*/
	Asteroid(float _x, float _y, int numberOfEdges = 3, float _radius = 15, float _angle = Maths::Random(0, 360), float velX = 0, float velY = 0, float _maxSpeed = Maths::Random(1.0f, 3.0f));
	Asteroid() {}

	/*
	//Render() draws the asteroid to the screen
	*/
	void Render();
	/*
	//Boost() adds a fixed value to the velocity component
	*/
	void Boost();
	/*
	//UpdatePos() calculates the asteroid's next x and y positions based on the velocity and applies the changes
	*/
	void UpdatePos();
	/*
	//PositionClamping() checks if the asteroid is outside the play area and wraps it if so
	*/
	void PositionClamping();
	/*
	//CheckHit() returns true if the distance between the passed x and y position plus the offset (IE shield) is greater than it's radius
	*/
	bool CheckHit(float _x, float _y, float offset = 0);
	/*
	//GetRadius() returns the radius of the asteroid
	*/
	float GetRadius() { return radius; }
	/*
	//GetX() returns the x component of the asteroid's position
	*/
	float GetX() { return x; }
	/*
	//GetY() returns the y component of the asteroid's position
	*/
	float GetY() { return y; }
	/*
	//GetNagle() returns the direction the asteriod is moving
	*/
	float GetAngle() { return angle; }
	/*
	//GetVelocityX() returns the asteroid's x velocity component
	*/
	float GetVelocityX() { return velocity[0]; }
	/*
	//GetVelocityY() returns the asteroid's y velocity compnent
	*/
	float GetVelocityY() { return velocity[1]; }
	/*
	//GetMaxSpeed() returns the asteroid's max speed
	*/
	float GetMaxSpeed() { return maxSpeed; }


private:
	/*
	//InitPointFactors() calculates a random value that will be added or subtracted to the distance between a point and the origin
	//to give the asteroid's a more rugged look
	*/
	void InitPointFactors();
	/*
	//InitPoints() calculates the x and y positions of all the asteroid's vertecies 
	*/
	void InitPoints();

	///////////////////////////////////////////////////////////////
	
	/*
	//x and y store the x and y position of the asteroid respectively
	//complexity stores how many edges or vertecies the asteroid has
	//points stores the positions of the vertecies of the asteroid
	//pointFactors stores the value to be subtracted from any given point to give it a jagged look
	//radius stores the aproximate radius of the asteroid depending on the pointFactors. However this radius is used for collision detection
	//velocity stores the x and y cmponents of the velocity in [0] and [1] respectively
	//damping is the factor applied to the velocity each frame
	//max speed is the maximum value each of the velocity components can be
	//angle stores the direction the asteroid is heading in degrees
	*/
	float x, y;
	int complexity;
	std::vector<std::vector<float>> points;
	std::vector<float> pointFactors;
	float radius;
	float velocity[2] = { 0,0 };
	float damping = 0.99f;
	float maxSpeed;
	float angle;


	
};

