#pragma once
#include "WindGenerator.h"
#include <iostream>

class WhirlWindGenerator : public WindGenerator {
private:
	float radius;
	float k;
	float height;

public:
	WhirlWindGenerator(Vector3 Pos, float Radius, float K) : radius(Radius* Radius), k(K), height(20), WindGenerator(Vector3(0, 0, 0), 1, 0, Pos, {Radius, 50, Radius}) {};

	virtual Vector3 getForce(Object* particle) {
		wind = (particle->getPos() - pos);
		if (radius < wind.magnitudeSquared())
			return Vector3(0, 0, 0);

		wind = Vector3(-wind.z, height - wind.y, wind.x);
		wind *= k;
		return WindGenerator::getForce(particle);
	}
};