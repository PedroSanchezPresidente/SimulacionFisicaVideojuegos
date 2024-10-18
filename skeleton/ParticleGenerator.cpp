#include "ParticleGenerator.h"

void ParticleGenerator::generarParticulas(std::list<Particle*> &particulas, double t) {
	timer += t;
	int cont = timer / rate;
	timer -= rate * cont;
	for (int i = 0; i < cont; i++) {
		Particle* p = new Particle(pos, dir, Vector3(1, 1, 1), Vector3(0, 0, 0), 1, shape, lifeTime);
		particulas.push_back(p);
		numPar++;
	}
}