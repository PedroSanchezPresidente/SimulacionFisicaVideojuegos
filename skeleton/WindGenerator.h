#pragma once
#include "ForceGenerator.h"

class WindGenerator : public ForceGenerator {
protected:
	float k1, k2;
	Vector3 wind;
	Vector3 size;
public:
	WindGenerator(Vector3 Wind, float K1, float K2 = 0, Vector3 Pos = Vector3(0,0,0), Vector3 Size = Vector3(0,0,0)) : ForceGenerator(Pos), wind(Wind), k1(K1), k2(K2), size(Size) {};

	virtual Vector3 getForce(Object* particle) {
		if (pos.x - size.x < particle->getPos().x && pos.x + size.x > particle->getPos().x && pos.y - size.y < particle->getPos().y && pos.y + size.y > particle->getPos().y) {
			Vector3 force = k1 * (wind - particle->getVel()) + k2 * (wind - particle->getVel()).magnitude() * (wind - particle->getVel());
			return force;
		}
		else
			return { 0,0,0 };
	}
};