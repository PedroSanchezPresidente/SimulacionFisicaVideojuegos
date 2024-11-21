#pragma once
#include "Particle.h"

enum ForceGeneratorTipe { GRAVITY, WIND, WHIRLWIND, EXPLOSION };

class ForceGenerator
{
public:
	ForceGenerator() {};

	virtual Vector3 getForce(Particle* p) = 0;
};

