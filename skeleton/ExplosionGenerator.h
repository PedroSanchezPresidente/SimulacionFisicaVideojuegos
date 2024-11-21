#pragma once
#include "ForceGenerator.h"
#include <cmath>

const float T;

class ExplosionGenerator : public ForceGenerator {
private:
	float k, radius, time = 0;

public:
	ExplosionGenerator(Vector3 Pos, float K, float Radius) : ForceGenerator(Pos), k(K), radius(Radius*Radius) {};

	virtual Vector3 getForce(Particle* particle) {
		Vector3 force = particle->getPos() - pos;
		if (radius < force.magnitudeSquared())
			return Vector3(0, 0, 0);

		force = (k / force.magnitudeSquared()) * force;
		force *= std::exp(-time/T);

		return force;
	}
};