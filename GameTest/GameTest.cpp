/*
//
//
//
//
//
//
//
//
//Jackson Zavarella's 2017 Ubisoft NXT Programming Competion Submission
//January 29th, 2017
//Email: Jzavarella@Ryerson.ca
//
//
//Appropriate documentation for all of the methods can be found in the appropriate header file
//
//
//
//
//
//
//
*/

//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <vector>
//------------------------------------------------------------------------
#include "app\app.h"
#include "Ship.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Maths.h"
#include "ShipExplosion.h"
#include "PowerUp.h"


using namespace App;
using namespace std;

/*
//ship stores teh player's ship
//roids stores all the asteroids in play
//powerUps stores all the powerUps in play
*/
Ship ship;
vector<Asteroid> roids;
vector<PowerUp> powerUps;

/*
//score stores the player's current score
//level stores the current level the player is on
*/
long score = 0;
int level = 1;

/*
//StartScreen, GameoverScreen, and level complete store which type of level should be rendered at that time
*/
bool StartScreen = true;
bool GameoverScreen = false;
bool levelComplete = false;

/*
//gunPressed stores whether the button to upgrade your gun is pressed
//turnPressed stores whether the button to upgrade your engines is pressed
*/
bool gunPressed = false;
bool turnPressed = false;

/*
//INITROIDS stores the initial number of asteroids on level one
*/
#define INITROIDS 2

/*
//MoreRoids() creates the number of asteroids passed to it. It also scales the average sive of each
//asteroid based on what level the player is on
*/
void MoreRoids(int numberOfAsteroids) {
	for (int i = 0; i < numberOfAsteroids; i++) {
		float xPos, yPos, radius;
		int numEdges;
		do {
			xPos = Maths::Random(0, APP_VIRTUAL_WIDTH);
			yPos = Maths::Random(0, APP_VIRTUAL_HEIGHT);
			numEdges = Maths::Random(5, 10);
			radius = Maths::Random(15, 70) + level * 5;
		} while (abs(Maths::Distance(xPos, yPos, ship.GetX(), ship.GetX())) < radius + 250);
		roids.push_back(Asteroid::Asteroid(xPos, yPos, numEdges, radius));
	}
}


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	/*
	//Resets everything that needs to be reset at the start of a new game or if the player presses R on the restart menu
	*/
	GameoverScreen = false;
	powerUps.clear();
	score = 0;
	level = 1;
	roids.clear();
	ship = Ship::Ship(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f, 15);
	MoreRoids(INITROIDS);
}

void Render();


//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	/*
	//Checks if any controls are pressed and updates the ship's position
	*/
	ship.CheckControls();
	ship.UpdatePos();
	ship.PositionClamping();

	/*
	//If not on the start screen check to see if the player has collied with a power up or asteroid or if the shield has collied with an asteroid
	//Destroy the player and go to game over if required
	*/
	if (!StartScreen) {

		for (int i = powerUps.size() - 1; i >= 0; i--) {
			if (powerUps[i].IsActive() && powerUps[i].CheckHit(ship.GetX(), ship.GetY())) {
				ship.StartInvincible();
				powerUps.erase(powerUps.begin() + i);
			}
		}

		for (int i = roids.size() - 1; i >= 0; i--) {
			Asteroid &currentAsteroid = roids[i];
			currentAsteroid.UpdatePos();
			currentAsteroid.PositionClamping();
			if (!GameoverScreen) {

				bool dead = false;
				
				if (!ship.IsInvincible()) {
					dead = roids[i].CheckHit(ship.GetX(), ship.GetY());
				}
				else if (roids[i].CheckHit(ship.GetX(), ship.GetY(), 100)) {
					score += 100;

					float xPos = currentAsteroid.GetX();
					float yPos = currentAsteroid.GetY();
					/*
					//If the radius of the destroyed asteroid is greater than 30, split it into two
					*/
					if (currentAsteroid.GetRadius() > 30) {
						float newRadius = currentAsteroid.GetRadius() / 1.6;
						float angle = Maths::Random(0, 360);
						float xVel = currentAsteroid.GetVelocityX();
						float yVel = currentAsteroid.GetVelocityY();
						float maxSpeed = currentAsteroid.GetMaxSpeed();
						roids.push_back(Asteroid::Asteroid(xPos, yPos, Maths::Random(5, 6), newRadius, -angle, xVel, yVel, maxSpeed));
						roids.push_back(Asteroid::Asteroid(xPos, yPos, Maths::Random(5, 6), newRadius, angle, xVel, yVel, maxSpeed));

					}
					roids.erase(roids.begin() + i);
				}
				if (dead) {

					ship.explosion = ShipExplosion::ShipExplosion(ship.GetX(), ship.GetY());
					ship.dead = dead;
					GameoverScreen = dead;
					break;

				}
				
				/*
				//Check to see if the lasers collide with any asteroids and delete/break them as required
				*/
				for (int j = ship.lasers.size() - 1; j >= 0; j--) {

					Laser &currentLaser = ship.lasers[j];
					if (currentAsteroid.CheckHit(currentLaser.GetX(), currentLaser.GetY())) {
						score += 100;

						float xPos = currentAsteroid.GetX();
						float yPos = currentAsteroid.GetY();
						/*
						//If the radius of the destroyed asteroid is bigger than 30, split it into two
						*/
						if (currentAsteroid.GetRadius() > 30) {
							float newRadius = currentAsteroid.GetRadius() / 1.6;
							float angle = Maths::Random(0, 360);
							float xVel = currentAsteroid.GetVelocityX();
							float yVel = currentAsteroid.GetVelocityY();
							float maxSpeed = currentAsteroid.GetMaxSpeed();
							roids.push_back(Asteroid::Asteroid(xPos, yPos, Maths::Random(5, 6), newRadius, -angle, xVel, yVel, maxSpeed));
							roids.push_back(Asteroid::Asteroid(xPos, yPos, Maths::Random(5, 6), newRadius, angle, xVel, yVel, maxSpeed));


						}
						//2% chance to drop a powerup
						if (Maths::Random(0, 1000) <= 20 && !ship.IsInvincible()) {
							powerUps.push_back(PowerUp::PowerUp(xPos, yPos));
						}
						roids.erase(roids.begin() + i);
						ship.lasers.erase(ship.lasers.begin() + j);



					}
				}
			}
		}
		/*
		//checks to see if the player has destroyed all the asteroids
		*/
		levelComplete = (roids.size() <= 0);
	}

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	/*
	//Start the background sound if its not played
	*/
	if (!IsSoundPlaying("sounds\\background.wav") && !levelComplete)
		PlaySound("sounds\\background.wav", true);

	/*
	//Render the ship
	*/
	ship.Render();

	/*
	//If not on the start screen, display the navigation section in the top left
	*/
	if (!StartScreen) {
		char scoreString[100] = "";
		sprintf(scoreString, "Score: %d Level: %d", score, level);
		Print(0, APP_VIRTUAL_HEIGHT - 18, scoreString);

		char gunString[13] = "";
		sprintf(gunString, "Gun Level: %d", ship.GetGunLevel());
		Print(0, APP_VIRTUAL_HEIGHT - 18 * 2, gunString);

		char turnString[18] = "";
		sprintf(turnString, "Rotation Level: %d", ship.GetTurnLevel());
		Print(0, APP_VIRTUAL_HEIGHT - 18 * 3, turnString);

		/*
		//If the ship is invincible, display the amount of time left on the shield
		*/
		if (ship.IsInvincible()) {
			char invincibleString[100] = "";
			sprintf(invincibleString, "Invincible Timer: %d", ship.GetInvincibleTimeLeft());
			Print(0, APP_VIRTUAL_HEIGHT - 18 * 4, invincibleString);
		}

		/*
		//Render the asteroids
		*/
		for (int i = roids.size() - 1; i >= 0; i--) {
			roids[i].Render();
		}

		/*
		//Render the power ups
		*/
		for (int i = 0; i < powerUps.size(); i++) {
			powerUps[i].Render();
		}
	}

	/*
	//Display the start screen and check for user input
	*/
	if (StartScreen & !GameoverScreen) {
		Print(APP_VIRTUAL_WIDTH / 2 - 50, APP_VIRTUAL_HEIGHT / 2 + 100, "ASTEROIDS");
		Print(APP_VIRTUAL_WIDTH / 2 - 60, APP_VIRTUAL_HEIGHT / 2 - 100, "Press 'S' to start");
		Print(APP_VIRTUAL_WIDTH / 2 - 75, APP_VIRTUAL_HEIGHT / 2 - 125, "Arrow keys to move");
		Print(APP_VIRTUAL_WIDTH / 2 - 70, APP_VIRTUAL_HEIGHT / 2 - 150, "Spacebar to shoot");
		if (IsKeyPressed('S'))
			StartScreen = false;
	}

	/*
	//Display the game over text and check for user input
	*/
	if (GameoverScreen && !StartScreen) {
		Print(APP_VIRTUAL_WIDTH / 2 - 50, APP_VIRTUAL_HEIGHT / 2 + 100, "GAMEOVER");
		Print(APP_VIRTUAL_WIDTH / 2 - 80, APP_VIRTUAL_HEIGHT / 2 - 100, "Press 'R' to Restart");
		if (IsKeyPressed('R'))
			Init();
	}

	/*
	//Check if the level is complete and display store information
	*/
	if (levelComplete) {

		/*
		//Clear the powerups on the screen
		*/
		powerUps.clear();

		/*
		//Stop the background music and play the shop music if its not playing
		*/
		StopSound("sounds\\background.wav");
		if (!IsSoundPlaying("sounds\\shoploop.wav"))
			PlaySound("sounds\\shoploop.wav", true);

		/*
		//Display the level clear text
		*/
		Print(APP_VIRTUAL_WIDTH / 2 - 60, APP_VIRTUAL_HEIGHT / 2 + 100, "LEVEL CLEAR!");
		Print(APP_VIRTUAL_WIDTH / 2 - 85, APP_VIRTUAL_HEIGHT / 2 - 100, "Press 'C' to Continue");

		/*
		//Display the upgrades and check for input if the player has not maxed them already
		*/
		if (ship.GetGunLevel() < 5) {
			/*
			//Calculate the cost of the upgrade based on current level
			*/
			int gunCost = 1000 * pow(ship.GetGunLevel() + 1, 2);
			//int gunCost = 0;
			char gunCostString[300] = "";

			sprintf(gunCostString, "Press '1' to upgrade gun (%d)", gunCost);

			Print(APP_VIRTUAL_WIDTH / 2 - 120, APP_VIRTUAL_HEIGHT / 2 - 200, gunCostString);

			if (IsKeyPressed('1')) {
				if (score >= gunCost && !gunPressed) {
					score -= gunCost;
					ship.UpgradeGun();
					gunPressed = true;
					PlaySound("sounds\\powerup-gun.wav");
				}
			}
			else {
				gunPressed = false;
			}
		}

		if (ship.GetTurnLevel() < 5) {
			int turnCost = 1000 * pow(ship.GetTurnLevel() + 1, 2);
			//int turnCost = 0;

			char turnCostString[300] = "";

			sprintf(turnCostString, "Press '2' to upgrade rotation (%d)", turnCost);

			Print(APP_VIRTUAL_WIDTH / 2 - 130, APP_VIRTUAL_HEIGHT / 2 - 225, turnCostString);

			if (IsKeyPressed('2')) {
				if (score >= turnCost && !turnPressed) {
					score -= turnCost;
					ship.UpgradeTurn();
					turnPressed = true;

					PlaySound("sounds\\powerup-turn.wav");
				}
			}
			else {
				turnPressed = false;
			}
		}

		/*
		//COntinue the game if the user presses C
		*/
		if (IsKeyPressed('C')) {
			level++;
			levelComplete = false;
			MoreRoids(INITROIDS + level);
			powerUps.clear();
		}
	}
	else {
		/*
		//Stop the shop sound
		*/
		StopSound("sounds\\shoploop.wav");
	}
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
}

