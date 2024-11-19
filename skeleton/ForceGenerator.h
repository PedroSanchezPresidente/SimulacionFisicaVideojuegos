#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator() {};
	virtual ~ForceGenerator() = 0;

	virtual Vector3 generarAcc(Particle p) = 0;
};

