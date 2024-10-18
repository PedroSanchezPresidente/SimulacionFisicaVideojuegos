#include "ParticleGenerator.h"

Particle* ParticleGenerator::generarParticula() {
	return new Particle(pos, dir, Vector3(0, 0, 0));
}