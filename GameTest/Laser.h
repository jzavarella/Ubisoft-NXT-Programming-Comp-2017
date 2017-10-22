/*
//The Laser class stoes all the methods and variables associated with the lasers shot by the ship
*/

#pragma once
class Laser
{
public:
	/*
	//Contructor for the laser which sets the initial x and y position and the initial direction the laser is going
	*/
	Laser(float _x, float _y, float _angle);
	Laser() {};

	/*
	//UpdatePos() claculates the next position the laser should be and updates the x and y accordingly
	*/
	void UpdatePos();
	/*
	//Render() draws the laser to the screen
	*/
	void Render();
	/*
	//OutOfBounds() returns true if the laser is off of the visible play screen
	*/
	bool OutOfBounds();
	/*
	//GetX() returns the laser's x position
	*/
	float GetX() { return x; }
	/*
	//GetY() returns the laser's y position
	*/
	float GetY() { return y; }
	
	/*
	//deleteMe stores whether or not the laser should eb deleted or not
	*/
	bool deleteMe = false;

private:
	/*
	//DrawBody() draws the laser's body to the screen
	*/
	void DrawBody();
	///////////////////////////////////////////

	/*
	//x, y, and angle store the x and y positions and the angle the laser is travelling respectively
	//speed stores the speed the laser is travelling
	//scale stores the number of pixels between the center and the outside edge of the square
	//soundPlayed stores whetter or not the laser has played its sounds
	*/
	float x, y, angle;
	float speed = 10;
	float scale = 2.5;
	bool soundPlayed = false;

};

