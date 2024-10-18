#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"

using namespace std;

class ParticleSystem
{
private:
	list<Particle*> particles;
	list<ParticleGenerator*> generators;

public:
	void update(double t);

};

