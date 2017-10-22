#include "stdafx.h"
#include <vector>
#include "Ship.h"
#include "App\app.h"
#include <math.h>
#include <chrono>
#include "Maths.h"
#include "ShipExplosion.h"

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;


using namespace App;
using namespace std;

#define FORWARD VK_UP // W 
#define BACKWARD VK_DOWN
#define LEFT VK_LEFT // A
#define RIGHT VK_RIGHT // D
#define SHOOT ' ' // ' '


Ship::Ship(float _x, float _y, float _scale)
{
	Ship::x = _x;
	Ship::y = _y;
	Ship::scale = _scale;

}

void Ship::Render() {
	if (!dead) {
		DrawBody();
		DrawLasers();
		if (invincible) {
			power.Render();
		}
	}
	else {
		explosion.Render();
	}
}



void Ship::UpdatePos() {
	if (!dead) {
		if (isBoosting)
			Boost();
		x += velocity[0];
		y += velocity[1];

		velocity[0] *= damping;
		velocity[1] *= damping;

		if (invincible) {
			power.SetPosition(x, y);
		}
	}
	if (invincible) {
		time_point<Clock> now = Clock::now();
		milliseconds diff = duration_cast<milliseconds>(now - invincibleTimer);
		if (diff.count() > shieldTimer) {
			invincible = false;
			power = PowerUp::PowerUp();
		}
	}


}

void Ship::PositionClamping() {
	if (x > APP_VIRTUAL_WIDTH + scale) {
		x = -scale;
	}
	else if (x < -scale) {
		x = APP_VIRTUAL_WIDTH + scale;
	}
	if (y > APP_VIRTUAL_HEIGHT + scale) {
		y = -scale;
	}
	else if (y < -scale) {
		y = APP_VIRTUAL_HEIGHT + scale;
	}
}

void Ship::Shoot() {
	lasers.push_back(Laser::Laser(x, y, angle));
}

void Ship::Rotate(float degrees) {
	angle += degrees;
}

void Ship::RotateLeft() {
	Ship::Rotate(rotationSpeed);
}
void Ship::RotateRight() {
	Ship::Rotate(-rotationSpeed);
}

void Ship::Boost() {
	if(velocity[0] >= -maxSpeed && velocity[0] <= maxSpeed)
		velocity[0] += cosf(Maths::Radians(angle + 90))*0.1f;
	if (velocity[1] >= -maxSpeed && velocity[1] <= maxSpeed)
		velocity[1] += sinf(Maths::Radians(angle + 90))*0.1f;
}

bool Ship::UpgradeGun() {

	if (gunLevel != 5) {
		gunLevel++;
		shotDelay -= gunLevel * 10;
		return true;
	}
	else return false;
}

bool Ship::UpgradeTurn() {

	if (turnLevel != 5) {
		turnLevel++;
		rotationSpeed += turnLevel * 0.3;
		PlaySound("sounds\powerup.wav");
		return true;
	}
	else return false;
}

void Ship::DrawBody() {

	float p1[2] = {  - scale,  - scale };
	float p2[2] = { 0,  + scale };
	float p3[2] = { scale,  - scale };
	float p4[2] = {-scale/5, 3/scale};
	float p5[2] = { scale / 5, 3 / scale };

	float temp = p1[0];
	p1[0] = Maths::RotateX(p1[0], p1[1], angle) + x;
	p1[1] = Maths::RotateY(temp, p1[1], angle) + y;

	temp = p2[0];
	p2[0] = Maths::RotateX(p2[0], p2[1], angle) + x;
	p2[1] = Maths::RotateY(temp, p2[1], angle) + y;

	temp = p3[0];
	p3[0] = Maths::RotateX(p3[0], p3[1], angle) + x;
	p3[1] = Maths::RotateY(temp, p3[1], angle) + y;

	temp = p4[0];
	p4[0] = Maths::RotateX(p4[0], p4[1], angle) + x;
	p4[1] = Maths::RotateY(temp, p4[1], angle) + y;

	temp = p5[0];
	p5[0] = Maths::RotateX(p5[0], p5[1], angle) + x;
	p5[1] = Maths::RotateY(temp, p5[1], angle) + y;

	DrawLine(p1[0], p1[1], p2[0], p2[1]);
	DrawLine(p2[0], p2[1], p3[0], p3[1]);
	DrawLine(p1[0], p1[1], p3[0], p3[1]);
	DrawLine(p4[0], p4[1], p5[0], p5[1]);
}

void Ship::DrawLasers() {
	for (int i = lasers.size() - 1; i >= 0; i--) {
		if (!lasers[i].deleteMe) {
			lasers[i].UpdatePos();
			lasers[i].Render();
		}
		else {
			lasers.erase(lasers.begin() + i);
		}
	}
}

void Ship::StartInvincible() {
	invincible = true;
	invincibleTimer = Clock::now();
	power = PowerUp::PowerUp(x, y, false);
	power.SetRadius(100);
}


void Ship::CheckControls() {
	if (IsKeyPressed(LEFT))
		RotateLeft();
	else if (IsKeyPressed(RIGHT))
		RotateRight();
	if (IsKeyPressed(FORWARD)) {
		isBoosting = true;
		Boost();
	}
	else
		isBoosting = false;
	if (IsKeyPressed(BACKWARD)) {
		damping = 0.9;
	}
	else
		damping = 0.99;
	if (IsKeyPressed(SHOOT)) {
		time_point<Clock> now = Clock::now();
		milliseconds diff = duration_cast<milliseconds>(now - lastShot);
		if (diff.count() > shotDelay) {
			Shoot();
			lastShot = Clock::now();
		}
	}
}

long Ship::GetInvincibleTimeLeft() {
	time_point<Clock> now = Clock::now();
	milliseconds diff = duration_cast<milliseconds>(now - invincibleTimer);
	return shieldTimer - diff.count();
}

