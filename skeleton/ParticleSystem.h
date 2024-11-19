#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"

using namespace std;

class ParticleSystem
{
private:
	list<Particle*> particles;
	list<ParticleGenerator*> particleGens;
	list<ForceGenerator*> forceGens;

public:
	~ParticleSystem() {
		for (Particle* p : particles)
			delete p;
		particles.clear();

		for (ParticleGenerator* g : particleGens)
			delete g;
		particleGens.clear();
	}

	void update(double t);

	void addGenerator(Vector3 pos, Vector3 minDir, Vector3 maxDir, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale);

	void addGenerator(Vector3 pos, float mean, Vector3 dev, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale);
};

