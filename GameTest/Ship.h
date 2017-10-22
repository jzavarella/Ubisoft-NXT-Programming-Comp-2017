/*
//The Ship class stores all the methods and variables associated with 
//the player controlled ship
*/


#include "Laser.h"
#include <vector>
#include <chrono>
#include "ShipExplosion.h"
#include "PowerUp.h"

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

#pragma once
class Ship
{
public:
	/*
	//Constructor for the Ship
	//_x and _y are the initial coordinates for the ship
	//scale is the factor of the size of the ship 
	//(15px * scale)
	*/
	Ship(float _x = 0, float _y = 0, float _scale = 1);

	/*
	//Render() Renders the ship
	*/
	void Render();
	/*
	//RotateLeft() rotates the ship by the negative private variable rotationSpeed
	*/
	void RotateLeft();
	/*
	//RotateRight() rotates the ship by the private variable rotationSpeed
	*/
	void RotateRight();
	/*
	// CheckControls() checks to see if the user has pressed any buttons
	*/
	void CheckControls();
	/*
	//UpdatePos() calculates what the next position of the ship should be based on the velocity
	*/
	void UpdatePos();
	/*
	//Boost() increases the velocity vector by a fixed amount
	*/
	void Boost();
	/*
	//PositionClamping() checks if the ship is off the screen and if so sets the x and y to wrap around the screen
	*/
	void PositionClamping();
	/*
	//Shoot() creates a laser at the ships position and heading
	*/
	void Shoot();
	/*
	//GetX() returns the ship's x position
	*/
	float GetX() { return x; }
	/*
	//GetY() returns the ship's y position
	*/
	float GetY() { return y; }
	/*
	//UpgradeGun() upgrades the gun level by one and applies the fire rate changes
	*/
	bool UpgradeGun();
	/*
	//UpgradeTurn() upgrades the turn level by one and applies the turn rate changes
	*/
	bool UpgradeTurn();
	/*
	//GetGunLevel() returns the ship's current gun level
	*/
	int GetGunLevel() { return gunLevel; }
	/*
	//GetTurnLevel() returns the ship's current turn level
	*/
	int GetTurnLevel() { return turnLevel; }
	/*
	//StartInvincible() makes the ship invinicible, creates the shield around the body, and starts the countdown timer
	*/
	void StartInvincible();
	/*
	//IsInvincible() returns if the ship is currently invincible
	*/
	bool IsInvincible(){ return invincible; }
	/*
	//GetInvincibleTimeLeft() returns how much time the ship will be invincible for in milliseconds
	*/
	long GetInvincibleTimeLeft();

	///////////////////////////////////

	/*
	//dead stores whether the ship is dead or alive
	*/
	bool dead = false;
	/*
	//lasers stores all of the lasers that the ship has fired
	*/
	std::vector<Laser> lasers;
	/*
	//explosion stores the ship's explosion object if it is dead
	*/
	ShipExplosion explosion;
	
	
private:
	/*
	//Rotate(float degrees) rotates the ship by the passed in angle in degrees
	*/
	void Rotate(float degrees);
	/*
	//DrawBody() draws the ship's body
	*/
	void DrawBody();
	/*
	//DrawLasers() draws each of the lasers in the lasers vector
	*/
	void DrawLasers();

	/*
	//x and y are the position components of the ship
	//angle stores the angle that the ship is pointing (0 being up)
	//rotationSpeed is the speed the ship will rotate at
	//velocity[2] is the current velocity components of the ship(velocity[0] being the x component and velocity[1] being the y)
	//isBoosting stores whether the player is pushing the forward key
	//damping stores how much the velocity should decrease by each frame if the the player is not boosting
	//maxSpeed is the greates either of the x and y components of the velocity can be
	//lastShot stores the time that the last laser shot was fired at
	//shotDelay is the time to wait between each laser shot
	//gunLevel stores the ships current gun level
	//turnLevel stores the ships current turn level
	//invincible stores whether the ship has a shield or not
	//invincibleTimer stores how long the ship has been invincible for
	//shieldTimer stores the maximum time the ship can be invincible for from one power up
	//power stores which power up the ship has
	*/
	float x, y, scale;
	float angle = 0;
	float rotationSpeed = 3;
	float velocity[2] = {0,0};
	bool isBoosting = false;
	float damping = 0.99f;
	float maxSpeed = 3.0f;
	time_point<Clock> lastShot = Clock::now();
	long shotDelay = 200;
	int gunLevel = 0;
	int turnLevel = 0;
	bool invincible = false;
	time_point<Clock> invincibleTimer;
	long shieldTimer = 10000;
	PowerUp power;


};

