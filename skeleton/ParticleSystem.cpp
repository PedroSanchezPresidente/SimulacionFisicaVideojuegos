#include "ParticleSystem.h"

void ParticleSystem::update(double t) {
	for (Particle* p : particles) {
		p->integrade(t);
	}
}