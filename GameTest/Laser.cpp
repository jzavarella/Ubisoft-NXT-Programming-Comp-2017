#include "stdafx.h"
#include "Laser.h"
#include "App\app.h"
#include <math.h>
#include "Maths.h"

using namespace App;

Laser::Laser(float _x, float _y, float _angle)
{
	Laser::x = _x;
	Laser::y = _y;
	Laser::angle = _angle;
}

void Laser::Render() {
	if (!soundPlayed) {
		soundPlayed = true;
		PlaySound("sounds\\shot.wav");
	}
	if (!OutOfBounds())
		DrawBody();
}

void Laser::DrawBody() {
	float p1[2] = { -scale, scale };
	float p2[2] = { scale, scale };
	float p3[2] = { scale, -scale };
	float p4[2] = { -scale, -scale };

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

	DrawLine(p1[0], p1[1], p2[0], p2[1]);
	DrawLine(p3[0], p3[1], p2[0], p2[1]);
	DrawLine(p3[0], p3[1], p4[0], p4[1]);
	DrawLine(p4[0], p4[1], p1[0], p1[1]);


}

bool Laser::OutOfBounds() {
	deleteMe = (x > APP_VIRTUAL_WIDTH + 2 * scale) || (x < 0 - 2 * scale) || (y > APP_VIRTUAL_HEIGHT + 2 * scale) || (y < 0 - 2 * scale);
	return deleteMe;
}

void Laser::UpdatePos() {
	x += cosf(Maths::Radians(angle + 90))*speed;
	y += sinf(Maths::Radians(angle + 90))*speed;
}

