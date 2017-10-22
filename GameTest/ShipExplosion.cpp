#include "stdafx.h"
#include "ShipExplosion.h"
#include "Maths.h"

#include "App\app.h"

using namespace App;

ShipExplosion::ShipExplosion(float _x, float _y)
{
	ShipExplosion::x = _x;
	ShipExplosion::y = _y;

	ShipExplosion::InitPoints();
}

void ShipExplosion::InitPoints() {
	points.clear();
	for (int i = 0; i < numberOfLines; i++) {
		float angle = PI * 2 / numberOfLines * i;

		float p1x = offCenter*cosf(angle) + x;
		float p1y = offCenter*sinf(angle) + y;
		points.push_back({p1x, p1y});

		float p2x = (offCenter + lineLength)*cosf(angle) + x;
		float p2y = (offCenter + lineLength)*sinf(angle) + y;
		points.push_back({ p2x, p2y });
	}
}

void ShipExplosion::Render() {
	if (!playedSound) {
		playedSound = true;
		PlaySound("sounds\\dying.wav");
	}
	for (int i = 0; i < points.size(); i+=2) {
		float p1x = points[i][0];
		float p1y = points[i][1];

		float p2x = points[i + 1][0];
		float p2y = points[i + 1][1];
		DrawLine(p1x, p1y, p2x, p2y);

		offCenter++;
		ShipExplosion::InitPoints();
	}
}

