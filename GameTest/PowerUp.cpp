#include "stdafx.h"
#include "PowerUp.h"
#include "App\app.h"
#include "Maths.h"

using namespace App;

PowerUp::PowerUp(float _x, float _y, bool _active)
{

	PowerUp::x = _x;
	PowerUp::y = _y;
	PowerUp::active = active;

	PowerUp::DetermineType();
	PowerUp::InitPoints();
	PowerUp::Render();
}

void PowerUp::DetermineType() {
	//type = Maths::Random(0, 1);
	type = 0;
	switch (type)
	{
	case 0: //Powerup one
		color = { 0.0f,0.7f,1.0f };
		numberOfEdges = 10;
	default:
		break;
	}
}

void PowerUp::InitPoints() {
	points.clear();
	for (int i = 0; i < numberOfEdges; i++) {
		float angle = PI * 2 / numberOfEdges * i;

		float p1x = radius*cosf(angle);
		float p1y = radius*sinf(angle);
		points.push_back({ p1x, p1y });
		
	}
}

void PowerUp::Render() {
	for (int i = 0; i < points.size(); i++) {
		if (i + 1 < points.size()) {
			DrawLine(points[i][0] + x, points[i][1] + y, points[i + 1][0] + x, points[i + 1][1] + y, color[0], color[1], color[2]);
		}
		else {
			DrawLine(points[i][0] + x, points[i][1] + y, points[0][0] + x, points[0][1] + y, color[0], color[1], color[2]); //close shape
		}
	}
}

bool PowerUp::CheckHit(float _x, float _y) {

	return (abs(Maths::Distance(x, y, _x, _y) < radius));
}