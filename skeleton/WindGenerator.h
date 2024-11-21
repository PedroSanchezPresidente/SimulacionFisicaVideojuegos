#pragma once
#include "ForceGenerator.h"

class WindGenerator : public ForceGenerator {
private:
	float k1, k2;
	Vector3 wind;
public:
	WindGenerator(Vector3 Wind, float K1, float K2 = 0) : wind(Wind), k1(K1), k2(K2) {};

	virtual Vector3 getForce(Particle* particle) {
		Vector3 force = k1 * (wind - particle->getVel()) + k2 * (wind - particle->getVel()).magnitude() * (wind - particle->getVel());
		return force;
	}
};