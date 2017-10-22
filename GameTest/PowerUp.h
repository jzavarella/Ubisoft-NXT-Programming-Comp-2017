/*
//PowerUp is the class that stores all of the details about
//any player collectable power up
*/

#include <vector>

#pragma once
class PowerUp
{
public:
	/*
	//Constructor for the class that sets the position for the power up and
	//an optional boolean which stores whether the powerup is collectble
	*/
	PowerUp(float _x, float _y, bool _active = true);
	PowerUp() {}

	/*
	//Render() draws the body of the power up to the screen
	*/
	void Render();
	/*
	//InitPoints() calculates all of the points of the power up depending on the x and y and numberOfEdges variable
	*/
	void InitPoints();
	/*
	//DetermineType() randomly generates the type of powerup and assigns the appropriate number of edges and colour
	*/
	void DetermineType();
	/*
	//CheckHit() returns true if the passed x and y coordinates are within the radius of the power up
	*/
	bool CheckHit(float _x, float _y);
	/*
	//GetType() returns the type of power up
	*/
	int GetType() { return type; }
	/*
	//IsActive() returns whether the power up can be picked up by the player
	*/
	bool IsActive() { return active; }
	/*
	//SetRadius() sets the pow up's radius to the passed in value and recalculates the vertecies
	*/
	void SetRadius(float r) { radius = r; InitPoints(); }
	/*
	//SetPosition() sets the power up's x and y components to the passed in _x and _y
	*/
	void SetPosition(float _x, float _y) { x = _x; y = _y; }
	

private: 
	/*
	//x and y store the current position of the origin of the power up
	//type stores an int that represents the type of power up. -1 is none, 0 is invincible, etc...
	//radius stores the distance from the origin to each vertex
	//points stores all the power up's vertiecies
	//color stores the RGB values for the color for the power up in the first three index positions. Values are between 0.0f and 1.0f
	//numberOfEdges is the the number of edges or vertecies the body has
	//active stores if the power up can be picked up by the player
	*/
	float x, y;
	int type = -1;
	float radius = 20;
	std::vector<std::vector<float>> points;
	std::vector<float> color;
	int numberOfEdges;
	bool active;
};

