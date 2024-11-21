#pragma once
#include "Particle.h"

enum ForceGeneratorTipe { GRAVITY, WIND, WHIRLWIND, EXPLOSION };

class ForceGenerator
{
protected:
	Vector3 pos;

public:
	ForceGenerator(Vector3 Pos) : pos(Pos){};

	virtual Vector3 getForce(Particle* p) = 0;
};

