#include "ParticleSystem.h"

void ParticleSystem::update(double t) {

	for (ParticleGenerator* g : generators) {
		g->generarParticulas(particles, t);

		int cont = g->getNumeroParticula();

		auto it = particles.begin();
		while (cont > 0) {
			if ((*it)->getLifeTime() <= 0 || ((*it)->getPos() - g->getPos()).magnitudeSquared() > g->getRadio()) {
				delete *it;
				auto aux = it;
				++aux;
				particles.erase(it);
				it = aux;
			}
			else
				(*it)->integrade(t);
			++it;
			cont--;
		}
	}

}

void ParticleSystem::addGenerator(Vector3 pos, Vector3 dir, float radio, float lifeTime, float ratio,ParticleType type) {
	generators.push_back(new ParticleGenerator(pos, dir, radio,lifeTime, ratio, type));
}