#include "ParticleSystem.h"
#include "iostream"

void ParticleSystem::update(double t) {

	for(ParticleGenerator* g : particleGens)
		g->generarParticulas(particles, t);
		
	auto it = particles.begin();
	while (it != particles.end()) {
		if ((*it)->isAlive()) {
			(*it)->integrade(t);
			++it;
		}
		else {
			auto aux = it;
			++it;
			delete *aux;
			particles.erase(aux);
		}
	}

}

void ParticleSystem::addGenerator(Vector3 pos, Vector3 minDir, Vector3 maxDir, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale) {
	particleGens.push_back(new ParticleGenerator(pos, minDir, maxDir, radio,lifeTime, ratio, color, transparencia, scale));
}

void ParticleSystem::addGenerator(Vector3 pos, float mean, Vector3 dev, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale) {
	particleGens.push_back(new ParticleGenerator(pos, mean, dev, radio, lifeTime, ratio, color, transparencia, scale));
}