#include "ParticleSystem.h"
#include "iostream"

void ParticleSystem::update(double t) {

	for(ParticleGenerator* g : particleGens)
		g->generarParticulas(particles, t);
		
	auto it = particles.begin();
	while (it != particles.end()) {
		if ((*it)->isAlive()) {
			Vector3 totalForce = Vector3(0,0,0);
			for (int i : *(*it)->getForceGenerator())
				totalForce += forceGens[i]->getForce(*it);
			(*it)->setAcceleration(totalForce / (*it)->getMasa());
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

int ParticleSystem::addParticleGenerator(Vector3 pos, Vector3 minDir, Vector3 maxDir, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale, float Masa ,vector<int>* FGIndex) {
	particleGens.push_back(new ParticleGenerator(pos, minDir, maxDir, radio,lifeTime, ratio, color, transparencia, scale));
	return particleGens.size() - 1;
}

int ParticleSystem::addParticleGenerator(Vector3 pos, float mean, Vector3 dev, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale, float Masa, vector<int>* FGIndex) {
	particleGens.push_back(new ParticleGenerator(pos, mean, dev, radio, lifeTime, ratio, color, transparencia, scale));
	return particleGens.size() - 1;
}

void ParticleSystem::asociateForceGenerator(int ParticleGeneratorIndex, int ForceGeneratorIndex) {
	particleGens[ParticleGeneratorIndex]->addForceGenerator(ForceGeneratorIndex);
}

void ParticleSystem::asociateForceGeneratorToAll(int ForceGeneratorIndex) {
	for (ParticleGenerator* g : particleGens)
		g->addForceGenerator(ForceGeneratorIndex);
}

int ParticleSystem::addForceGenerator(ForceGeneratorTipe tipe, Vector3 force, float k) {
	switch (tipe)
	{
	case GRAVITY:
		forceGens.push_back(new GravityGenerator(force));
		break;
	case WIND:
		forceGens.push_back(new WindGenerator(force, k));
		break;
	case WHIRLWIND:
		break;
	case EXPLOSION:
		break;
	default:
		break;
	}

	return forceGens.size() - 1;
}