#pragma once
#include "Particle.h"

class ParticleGenerator
{
private:
	Vector3 pos;
	Vector3 dir;
	int radio;
	int iniTimer;
	int timer;

public:
	ParticleGenerator(Vector3 Pos, Vector3 Dir, int Radio, int IniTimer) : pos(pos), dir(Dir), radio(Radio), iniTimer(IniTimer) { timer = iniTimer; };

	Particle* generarParticula();
};

