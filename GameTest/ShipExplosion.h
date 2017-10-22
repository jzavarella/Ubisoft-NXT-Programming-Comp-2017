/*
///A class that stores all the functions and methods associated with
///the ship explosion

*/

#include <vector>

#pragma once
class ShipExplosion
{
public:
	/*
	//Constructor for the Ship Explosion which sets the position
	//to the passed in floats
	*/
	ShipExplosion(float _x, float _y);
	ShipExplosion() {};

	/*
	//Render() renders the ship explosion entities
	*/
	void Render();
	/*
	//InitPoints() calculates all of the points of each line of the explosion
	*/
	void InitPoints();

private:
	/*
	//x and y store the position of the origin of the explosion
	//lineLength stores the length of each explosion streak
	//offCenter store the initial distance between the origin and each streak
	//points is a vector that stores each vertex 
	//playSound is used to know if the explosion sound should be played
	*/
	float x, y;
	float lineLength = 15.0f;
	float offCenter = 5.0f;
	int numberOfLines = 8;
	std::vector<std::vector<float>> points;
	bool playedSound = false;
};

