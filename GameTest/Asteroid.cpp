#include "stdafx.h"
#include "Asteroid.h"
#include "App\app.h"
#include "Maths.h"
#include "Laser.h"

using namespace App;
using namespace std;

Asteroid::Asteroid(float _x, float _y, int numberOfEdges, float _radius, float _angle, float velX, float velY, float _maxSpeed)
{
	Asteroid::x = _x;
	Asteroid::y = _y;
	Asteroid::complexity = numberOfEdges;
	Asteroid::radius = _radius;
	Asteroid::angle = _angle;
	Asteroid::velocity[0] = velX;
	Asteroid::velocity[1] = velY;
	Asteroid::maxSpeed = _maxSpeed;

	Asteroid::InitPointFactors();
	Asteroid::InitPoints();
}


void Asteroid::InitPointFactors() {
	for (int i = 0; i < complexity; i++) {
		pointFactors.push_back(Maths::Random(-radius / 5, radius / 5));
	}
}

void Asteroid::InitPoints() {
	for (int i = 0; i < complexity; i++) {
		float angle = PI * 2 / complexity * i; // map i between 0 and two pi
		float thisFactor = radius + pointFactors[i];
		points.push_back({ thisFactor * cosf(angle), thisFactor * sinf(angle) });
	}
}

void Asteroid::Render() {
	for (int i = 0; i < points.size(); i++) {
		if (i + 1 < points.size()) {
			DrawLine(points[i][0] + x, points[i][1] + y, points[i + 1][0] + x, points[i + 1][1] + y);
		}
		else {
			DrawLine(points[i][0] + x, points[i][1] + y, points[0][0] + x, points[0][1] + y); //close shape
		}
	}
}

void Asteroid::Boost() {
	
		if (velocity[0] >= -maxSpeed && velocity[0] <= maxSpeed)
			velocity[0] += cosf(Maths::Radians(angle + 90))*0.1f;
		if (velocity[1] >= -maxSpeed && velocity[1] <= maxSpeed)
			velocity[1] += sinf(Maths::Radians(angle + 90))*0.1f;
	
}

void Asteroid::UpdatePos() {
	Boost();
	x += velocity[0];
	y += velocity[1];

	velocity[0] *= damping;
	velocity[1] *= damping;
}



bool Asteroid::CheckHit(float _x, float _y, float offset) {

	return (abs(Maths::Distance(x, y, _x, _y) < radius + offset));
}


void Asteroid::PositionClamping() {
	if (x > APP_VIRTUAL_WIDTH + radius) {
		x = -radius;
	}
	else if (x < -radius) {
		x = APP_VIRTUAL_WIDTH + radius;
	}
	if (y > APP_VIRTUAL_HEIGHT + radius) {
		y = -radius;
	}
	else if (y < -radius) {
		y = APP_VIRTUAL_HEIGHT + radius;
	}
}


