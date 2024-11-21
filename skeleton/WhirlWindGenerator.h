#pragma once
#include "WindGenerator.h"
#include <iostream>

class WhirlWindGenerator : public WindGenerator {
private:
	float radius;
	float k;

public:
	WhirlWindGenerator(Vector3 Pos, float Radius, float K) : radius(Radius* Radius), k(K), WindGenerator(Vector3(0,0,0), 1, 0, Pos){};

	virtual Vector3 getForce(Particle* particle) {
		wind = (particle->getPos() - pos);
		if (radius < wind.magnitudeSquared())
			return Vector3(0, 0, 0);

		wind = Vector3(-wind.z, 50 - wind.y, wind.x);
		wind *= k;
		return WindGenerator::getForce(particle);
	}
};